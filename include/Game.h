#pragma once

#include "Gameboard.h"
#include "SpecialTileUsage.h"
#include "TileEnums.h"
#include <array>
#include <variant>
#include <vector>

struct DiceRoll
{
	TileType dice1;
	TileType dice2;
	TileType dice3;
	TileType dice4;
};

struct EndTurn
{
};
using Action = std::variant<Move, EndTurn, DiceRoll>;

struct ChanceOutcome
{
	DiceRoll roll;
	double probability;
};

class Game
{
  public:
	explicit Game(Gameboard gameboard);

	bool isChanceNode() const { return phase() == Phase::AwaitingRoll; }
	// Stub until chance outcome generation is implemented.
	std::vector<ChanceOutcome> chanceOutcomes() const;
	// Decision actions only. Use chanceOutcomes() while awaiting a roll.
	std::vector<Action> legalActions() const;
	// Throws std::invalid_argument if the action is illegal in this state.
	void applyAction(const Action &action);
	bool isGameOver() const { return phase() == Phase::Terminal; }
	Score getScore() const;
	// Number of completed rounds.
	int getTurnNumber() const { return turn; }

  private:
	enum class Phase { AwaitingRoll, PlacingTiles, Terminal };
	Phase phase() const;
	void appendPlacements(TileType type, std::vector<Action> &actions) const;
	bool canUseSpecial(TileType type) const;

	Gameboard gameboard;
	int turn{ 0 };
	// True once the round's full four-die roll has been applied.
	bool rollApplied{ false };
	// Number of unspent dice showing each TileType.
	std::array<int, NumTiles> remainingDice{};
	SpecialTileUsage specialTilesUsed;
	int specialTilesPlaced{ 0 };
	bool specialPlacedThisRound{ false };
};
