#pragma once
#include "Gameboard.h"
#include "SpecialTileUsage.h"
#include "TileEnums.h"
#include <optional>
#include <vector>

using TurnMoves = std::array<std::optional<Move>, 5>;


struct DiceRoll
{
	TileType dice1;// Route Die 1
	TileType dice2;// Route Die 2
	TileType dice3;// Route Die 3
	TileType dice4;// Other Die
};

class Game
{

  public:
	explicit Game(Gameboard gameboard);
	void applyTurn(const TurnMoves &moves);
	std::optional<TurnMoves> pickLegalTurn(const DiceRoll &roll) const;
	bool isGameOver() const;
	Score getScore() const;// TODO: calculateScore owned by gameboard
	int getTurnNumber() const { return turn; }

  private:
	Gameboard gameboard;
	int turn{ 0 };
	SpecialTileUsage specialTilesUsed;
};
