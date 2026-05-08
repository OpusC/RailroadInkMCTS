#include "Gameboard.h"
#include "BoardExit.h"
#include "Debug.h"
#include "TileEnums.h"
#include "Tiles.h"
#include <array>
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

	for (std::size_t i = 0; i < exits.size(); i++) {
		for (std::size_t j = i + 1; j < exits.size(); j++) {
			assert(exits[i].boardX != exits[j].boardX
			       || exits[i].boardY != exits[j].boardY);
		}
	}

	for (BoardExit exit : exits) {
		int directions[4][2] = { { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 } };
		// +1 at the end is required because board size is actually larger
		// than the exposed interface because exits are on the board
		// but not exposed publically
		LOG_DEBUG << "Direction " << exit.exitDirection << " add "
		          << directions[exit.exitDirection][0] << "to x" << '\n';
		LOG_DEBUG << "Direction " << exit.exitDirection << " add "
		          << directions[exit.exitDirection][1] << "to y" << '\n';
		auto x = exit.boardX + directions[exit.exitDirection][0] + 1;
		auto y = exit.boardY + directions[exit.exitDirection][1] + 1;

		TileType exitTileType;
		if (exit.connectionType == ConnectionType::Rail) {
			exitTileType = TileType::StraightRail;
		} else {
			exitTileType = TileType::StraightRoad;
		}

		Tile exitTile = Tile(exitTileType);

		// Either x is on an edge and y is anything
		// Or y is on an edge and x is anything
		LOG_DEBUG << "Placing exit tile at x : " << x << " y: " << y << "\n";
		LOG_DEBUG << "Total size " << totalSize << '\n';
		assert(
		  (x == 0 || x == totalSize - 1) || (y == 0 || y == totalSize - 1));

		// TODO: assert that the exit faces into the board

		if (exit.exitDirection % 2 != 0) { exitTile.rotate(); }

		gameboard[y][x] = exitTile;
	}
}

bool Gameboard::isMoveValid(const Move &move) const
{
	LOG_DEBUG << "isMoveValid for x: " << move.x << " y: " << move.y << '\n';
	std::array<std::array<int, 2>, 4> directions = {
		{ { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 } }
	};

	if (getTile(move.x, move.y).getTileType() != TileType::Empty) {
		LOG_DEBUG << "attempting to place tile on non-empty cell" << '\n';
		return false;
	}

	bool connects = false;


	for (std::size_t i = 0; i < directions.size(); i++) {
		int x = move.x + directions[i][0];
		int y = move.y + directions[i][1];

		connects = connects
		           || Tile::connects(
		             move.tile, getTile(x, y), static_cast<Direction>(i));

		LOG_DEBUG << "connects: " << connects << '\n';
	}

	return connects;
}

void Gameboard::removeTile(int x, int y)
{
	return;// TODO: STUB
}

/*
 * This method does not check if a move is valid. Use isMoveValid for that
 * purpose
 */
void Gameboard::applyMove(const Move &move)
{
	LOG_DEBUG << "Placed tile at x " << move.x + 1 << " y " << move.y + 1
	          << '\n';
	gameboard[move.y + 1][move.x + 1] = move.tile;
}

const Tile Gameboard::getTile(int x, int y) const
{
	LOG_DEBUG << "getTile x: " << x + 1 << ", y: " << y + 1 << "\n";
	assert(x >= -1 && x <= size);
	assert(y >= -1 && y <= size);
	return gameboard[y + 1][x + 1];
}

int Gameboard::getSize() const { return this->size; }
