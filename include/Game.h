#pragma once
#include "Gameboard.h"
#include "TileEnums.h"
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
	TileType dice1;// Route Die 1
	TileType dice2;// Route Die 2
	TileType dice3;// Route Die 3
	TileType dice4;// Other Die
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
	explicit Game(Gameboard gameboard, std::mt19937 rng);
	DiceRoll rollDice();
	void applyTurn(const Turn &turn);
	int getNumberOfSpecialTilesUsed() const;
	int getTurnNumber() const { return turn; }
	std::vector<Turn> generateLegalTurns(const DiceRoll &roll) const;
	bool isGameOver() const;
	Score getScore() const;// TODO: calculateScore owned by gameboard

  private:
	Gameboard gameboard;
	int turn;
	SpecialTileUsage specialTilesUsed;
	std::mt19937 rng;
};
