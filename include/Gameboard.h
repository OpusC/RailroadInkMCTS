#pragma once
#include "BoardExit.h"
#include "Move.h"
#include "Tiles.h"
#include <array>
#include <vector>

class Gameboard
{
  public:
	explicit Gameboard(int size, std::vector<BoardExit>);

	const Tile getTile(int x, int y) const;
	const std::vector<std::vector<Tile>> &getGameboard() const
	{
		return gameboard;
	}
	int getSize() const;

	bool isTilePlacementValid(int x, int y, const Tile &tile) const;

	void applyTurn(const Turn &turn);
	void removeTile(int x, int y);


  private:
	int size;
	std::vector<std::vector<Tile>> gameboard;
};
