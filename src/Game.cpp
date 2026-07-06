#include "Game.h"
#include "Gameboard.h"
#include <array>
#include <random>
#include <vector>

static const int maxRetries = 500;

static const std::array<TileType, 6> routeDie = { TileType::StraightRail,
	TileType::CurvedRail,
	TileType::TRail,
	TileType::StraightRoad,
	TileType::CurvedRoad,
	TileType::TRoad };

static const std::array<TileType, 6> specialDie = { TileType::RoadRailUnderpass,
	TileType::RoadRailUnderpass,
	TileType::RoadToRail,
	TileType::RoadToRail,
	TileType::CurvedRoadToRail,
	TileType::CurvedRoadToRail };

Game::Game(Gameboard gameboard)
  : gameboard(gameboard), turn(0), specialTilesUsed{}
{}

// TODO: complete this method
void Game::applyTurn(const TurnMoves &moves) { this->turn += 1; };

std::optional<TurnMoves> Game::pickLegalTurn(const DiceRoll &roll) const
{
	std::mt19937 rng{ std::random_device{}() };
	int boardSize = gameboard.getSize();

	std::array<TileType, 4> requiredTiles = {
		roll.dice1, roll.dice2, roll.dice3, roll.dice4
	};

	std::vector<TileType> availableSpecials;
	static const std::array<TileType, 6> specialTypes = { TileType::Special1,
		TileType::Special2,
		TileType::Special3,
		TileType::Special4,
		TileType::Special5,
		TileType::Special6 };

	// TODO: Might be better to keep this info stored in the class instead of
	// re-computing each time, but best to profile it first
	for (TileType t : specialTypes) {
		if (!specialTilesUsed.isUsed(t)) { availableSpecials.push_back(t); }
	}

	std::uniform_int_distribution<int> coordDist(0, boardSize - 1);
	std::uniform_int_distribution<int> rotDist(0, 3);

	for (int attempt = 0; attempt < maxRetries; attempt++) {
		TurnMoves moves{};
		// Scratch copy of the board so intra-turn placements are visible
		// to subsequent isMoveValid calls within the same turn attempt
		Gameboard tempBoard = gameboard;
		bool turnFailed = false;

		for (int d = 0; d < 4 && !turnFailed; d++) {
			bool placed = false;

			for (int retry = 0; retry < maxRetries && !placed; retry++) {
				int x = coordDist(rng);
				int y = coordDist(rng);
				int rotCount = rotDist(rng);

				Tile tile(requiredTiles[d], static_cast<Rotation>(rotCount));
				Move move{ tile, x, y };

				if (tempBoard.isMoveValid(move)) {
					tempBoard.applyMove(move);
					moves[d] = move;
					placed = true;
				}
			}

			if (!placed) { turnFailed = true; }
		}

		if (turnFailed) continue;

		// Optionally place one special tile using the same scratch board
		if (!availableSpecials.empty()) {
			std::uniform_int_distribution<int> specialDist(
			  0, static_cast<int>(availableSpecials.size()) - 1);

			for (int retry = 0; retry < maxRetries; retry++) {
				int x = coordDist(rng);
				int y = coordDist(rng);
				int rotCount = rotDist(rng);

				TileType specialType = availableSpecials[specialDist(rng)];
				Tile tile(specialType, static_cast<Rotation>(rotCount));
				Move move{ tile, x, y };

				if (tempBoard.isMoveValid(move)) {
					moves[4] = move;
					break;
				}
			}
			// Special placement failure is acceptable — slot 4 stays nullopt
		}

		return moves;
	}

	return std::nullopt;
}
