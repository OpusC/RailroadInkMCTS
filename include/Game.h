#pragma once
#include "Gameboard.h"
#include <array>
#include <random>
#include <vector>

struct SpecialTileUsage
{
	bool tileA;
	bool tileB;
	bool tileC;
	bool tileD;
	bool tileE;
	bool tileF;
};

struct DiceRoll
{
	std::array<TileType, 4> tiles;
};

struct Turn
{
	DiceRoll diceRoll;
	std::vector<Move> moves;
	bool usedSpecialTile;
};

class Game
{

  public:
	explicit Game(Gameboard gameboard, uint32_t seed);
	uint32_t getSeed() const;
	DiceRoll rollDice();
	void applyTurn(const Turn &turn);
	int getNumberOfSpecialTilesUsed() const;
	int getTurnNumber() const;
	std::vector<Turn> generateLegalTurns(const DiceRoll &roll) const;
	bool isGameOver() const;
	Score getScore() const;// TODO: calculateScore owned by gameboard

  private:
	Gameboard gameboard;
	int turn;
	SpecialTileUsage specialTilesUsed;
	const std::mt19937 rng;
};
