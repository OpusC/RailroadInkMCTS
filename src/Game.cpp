#include "Game.h"
#include <algorithm>
#include <stdexcept>
#include <utility>

namespace {
constexpr int roundLimit = 7;
constexpr int specialLimit = 3;

constexpr std::array<TileType, 6> otherDie = { RoadRailUnderpass,
	RoadRailUnderpass,
	RoadToRail,
	RoadToRail,
	CurvedRoadToRail,
	CurvedRoadToRail };
constexpr std::array<Rotation, 4> rotations = { Zero,
	Ninety,
	OneEighty,
	TwoSeventy };

bool isOtherDieFace(TileType type)
{
	return std::find(otherDie.begin(), otherDie.end(), type) != otherDie.end();
}
}// namespace

Game::Game(Gameboard gameboard) : gameboard(std::move(gameboard)) {}

Game::Phase Game::phase() const
{
	if (turn == roundLimit) { return Phase::Terminal; }
	return rollApplied ? Phase::PlacingTiles : Phase::AwaitingRoll;
}

std::vector<ChanceOutcome> Game::chanceOutcomes() const
{
	// TODO: Generate weighted outcomes for a full four-die roll.
	return {};
}

bool Game::canUseSpecial(TileType type) const
{
	return isSpecialTile(type) && !specialPlacedThisRound
	       && specialTilesPlaced < specialLimit
	       && !specialTilesUsed.isUsed(type);
}

void Game::appendPlacements(TileType type, std::vector<Action> &actions) const
{
	std::vector<Tile> orientations;
	for (Rotation rotation : rotations) {
		Tile tile(type, rotation);
		if (std::find(orientations.begin(), orientations.end(), tile)
		    == orientations.end()) {
			orientations.push_back(tile);
		}
	}

	for (int y = 0; y < gameboard.getSize(); ++y) {
		for (int x = 0; x < gameboard.getSize(); ++x) {
			for (const Tile &tile : orientations) {
				Move move{ tile, x, y };
				if (gameboard.isMoveValid(move)) { actions.emplace_back(move); }
			}
		}
	}
}

std::vector<Action> Game::legalActions() const
{
	std::vector<Action> actions;
	if (phase() != Phase::PlacingTiles) { return actions; }

	for (int index = 0; index < NumTiles; ++index) {
		if (remainingDice[index] > 0) {
			appendPlacements(static_cast<TileType>(index), actions);
		}
	}
	if (actions.empty()) { actions.emplace_back(EndTurn{}); }

	for (int index = Special1; index <= Special6; ++index) {
		const auto type = static_cast<TileType>(index);
		if (canUseSpecial(type)) { appendPlacements(type, actions); }
	}
	return actions;
}

void Game::applyAction(const Action &action)
{
	if (const auto *roll = std::get_if<DiceRoll>(&action)) {
		if (phase() != Phase::AwaitingRoll || !isRouteTile(roll->dice1)
		    || !isRouteTile(roll->dice2) || !isRouteTile(roll->dice3)
		    || !isOtherDieFace(roll->dice4)) {
			throw std::invalid_argument("Illegal dice roll");
		}
		for (TileType face :
		  { roll->dice1, roll->dice2, roll->dice3, roll->dice4 }) {
			++remainingDice[face];
		}
		rollApplied = true;
		return;
	}

	if (phase() != Phase::PlacingTiles) {
		throw std::invalid_argument(
		  "A roll is required before taking a placement action");
	}

	if (const auto *move = std::get_if<Move>(&action)) {
		const TileType type = move->tile.getTileType();
		const bool special = canUseSpecial(type);
		const int size = gameboard.getSize();
		if (type < 0 || type >= NumTiles
		    || (!special && remainingDice[type] == 0) || move->x < 0
		    || move->x >= size || move->y < 0 || move->y >= size
		    || !gameboard.isMoveValid(*move)) {
			throw std::invalid_argument("Illegal tile placement");
		}

		gameboard.applyMove(*move);
		if (special) {
			specialTilesUsed.markUsed(type);
			specialPlacedThisRound = true;
			++specialTilesPlaced;
		} else {
			--remainingDice[type];
		}
		return;
	}

	// EndTurn is generated first when no rolled tile can be placed.
	const auto actions = legalActions();
	if (!std::holds_alternative<EndTurn>(actions.front())) {
		throw std::invalid_argument("A rolled tile can still be placed");
	}
	remainingDice.fill(0);
	specialPlacedThisRound = false;
	rollApplied = false;
	++turn;
}

Score Game::getScore() const { return gameboard.calculateScore(); }
