#include "Gameboard.h"
#include "BoardExit.h"
#include "TileEnums.h"
#include "Tiles.h"
#include <cassert>
#include <vector>


Gameboard::Gameboard(int size, std::vector<BoardExit> exits)
  : size(size), gameboard(size + 2, std::vector<Tile>(size + 2))
{
	this->size = size;
	int totalSize = size + 2;

	using TT = TileType;

	for (int row = 0; row < totalSize; row++) {
		for (int col = 0; col < totalSize; col++) {

			if (row == 0 || row == totalSize - 1 || col == 0
			    || col == totalSize - 1) {
				gameboard[row][col] = Tile(TT::Border);
			} else {
				gameboard[row][col] = Tile(TT::Empty);
			}
		}
	}

	for (int i = 0; i < exits.size(); i++) {
		for (int j = i + 1; j < exits.size(); j++) {
			assert(exits[i].boardX != exits[j].boardX
			       || exits[i].boardY != exits[j].boardY);
		}
	}

	for (BoardExit exit : exits) {
		int directions[4][2] = { { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 } };
		auto x = exit.boardX + directions[exit.exitDirection][0];
		auto y = exit.boardY + directions[exit.exitDirection][1];

		TileType exitTileType;
		if (exit.connectionType == ConnectionType::Rail) {
			exitTileType = TileType::StraightRail;
		} else {
			exitTileType = TileType::StraightRoad;
		}

		Tile exitTile = Tile(exitTileType);


		if (exit.exitDirection % 2 != 0) { exitTile.rotate(); }

		gameboard[y + 1][x + 1] = exitTile;
	}
}

const Tile Gameboard::getTile(int x, int y) const
{
	assert(x >= 0 && x < size);
	assert(y >= 0 && y < size);
	return gameboard[y + 1][x + 1];
}

int Gameboard::getSize() const { return this->size; }
