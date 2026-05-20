#include "Gameboard.h"
#include "BoardExit.h"
#include "Debug.h"
#include "TileEnums.h"
#include "Tiles.h"
#include <array>
#include <cassert>
#include <iostream>
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
	printBoard();

	// UP, RIGHT, DOWN, LEFT
	std::array<std::array<int, 2>, 4> directions = {
		{ { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 } }
	};

	if (getTile(move.x, move.y).getTileType() != TileType::Empty) {
		LOG_DEBUG << "attempting to place tile on non-empty cell" << '\n';
		return false;
	}

	bool connects = false;
	for (std::size_t i = 0; i < directions.size(); i++) {

		LOG_DEBUG << "i " << i << '\n';

		auto reverseDirection = (i + 2) % (Direction::NumDirections);
		LOG_DEBUG << "reverse direction " << reverseDirection << '\n';

		int x = move.x + directions[i][0];
		int y = move.y + directions[i][1];

		Tile connectingTile = getTile(x, y);

		connects = connects
		           || Tile::connects(
		             move.tile, connectingTile, static_cast<Direction>(i));


		// Conditions
		// If we create a dead end, we instantly fail
		// If we have a valid connection, we mark as valid but continue
		// to iterate to check for a dead end
		// continue if ConnectionType is none so we don't early fail
		// otherwise check for a connection
		ConnectionType connectionType =
		  connectingTile.getConnections()[reverseDirection];
		if (connectionType != ConnectionType::None) {
			LOG_DEBUG << "Checking for dead end" << "\n";

			bool connectingTileCheck = Tile::connects(connectingTile,
			  move.tile,
			  static_cast<Direction>(reverseDirection));

			if (connectingTileCheck == false) { return false; }
		}


		LOG_DEBUG << "validTile: " << connects << '\n';
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
	// LOG_DEBUG << "getTile x: " << x + 1 << ", y: " << y + 1 << "\n";
	assert(x >= -1 && x <= size);
	assert(y >= -1 && y <= size);
	return gameboard[y + 1][x + 1];
}

int Gameboard::getSize() const { return this->size; }

static char renderTile(const Tile &tile)
{
	TileType tt = tile.getTileType();
	if (tt == TileType::Empty) return '.';
	if (tt == TileType::Border) return '#';
	if (isSpecialTile(tt)) return 'S';

	auto &c = tile.getConnections();
	bool up = c[Up] != ConnectionType::None;
	bool right = c[Right] != ConnectionType::None;
	bool down = c[Down] != ConnectionType::None;
	bool left = c[Left] != ConnectionType::None;

	// Use rail symbols when any connection is rail; road otherwise
	bool hasRail =
	  c[Up] == ConnectionType::Rail || c[Right] == ConnectionType::Rail
	  || c[Down] == ConnectionType::Rail || c[Left] == ConnectionType::Rail;

	int count = up + right + down + left;

	switch (count) {
	case 4:
		return '*';
	case 3:
		return hasRail ? 't' : 'T';
	case 2:
		if (up && down) return hasRail ? '|' : 'I';
		if (left && right) return hasRail ? '-' : '=';
		if (up && right) return hasRail ? 'l' : 'L';
		if (up && left) return hasRail ? 'j' : 'J';
		if (down && right) return hasRail ? 'f' : 'F';
		if (down && left) return hasRail ? 'z' : 'Z';
		break;
	case 1:
		return hasRail ? 'r' : 'R';// border exit stubs
	default:
		break;
	}
	return '?';
}

/*
 * printBoard renders the gameboard as ASCII characters, one char per tile.
 *
 * Fixed tiles:
 *   '.'  Empty cell
 *   '#'  Border
 *   'S'  Special tile
 *   '?'  Unknown/error
 *
 * Connection tiles use lowercase for rail and uppercase for road.
 * The shape of the character reflects the tile's orientation:
 *
 *   Straight:   '|' / 'I'  (vertical)     '-' / '='  (horizontal)
 *   Curved:     'l' / 'L'  (up + right)   'j' / 'J'  (up + left)
 *               'f' / 'F'  (down + right) 'z' / 'Z'  (down + left)
 *   T-junction: 't' / 'T'
 *   4-way:      '*'
 *   Exit stub:  'r' / 'R'  (single connection on the border)
 *
 * Example output (4x4 board with a horizontal rail crossing the middle):
 *   ######
 *   #....#
 *   #r--r#
 *   #....#
 *   #....#
 *   ######
 */
void Gameboard::printBoard() const
{
	int totalSize = size + 2;
	for (int row = 0; row < totalSize; row++) {
		for (int col = 0; col < totalSize; col++) {
			std::cout << renderTile(gameboard[row][col]);
		}
		std::cout << '\n';
	}
}
