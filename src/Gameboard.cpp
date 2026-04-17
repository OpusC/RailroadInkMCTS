#include "Gameboard.h"
#include "BoardExit.h"
#include "Debug.h"
#include "TileEnums.h"
#include "Tiles.h"
#include <array>
#include <cassert>
#include <set>
#include <unordered_set>
#include <utility>
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

void Gameboard::setTile(int x, int y, Tile tile)
{
	assert(x >= 0 && x < size);
	assert(y >= 0 && y < size);
	gameboard[y + 1][x + 1] = tile;
}

const Tile Gameboard::getTile(int x, int y) const
{
	assert(x >= 0 && x < size);
	assert(y >= 0 && y < size);
	return gameboard[y + 1][x + 1];
}

int Gameboard::getSize() const { return this->size; }

bool Gameboard::isConnected(std::array<Move, 5> moves)
{
	LOG_DEBUG << "inside isConnected method\n";
	// create 7x7 array
	std::set<Tile> visited = {};


	for (Move m : moves) {
		if (m.tile.getTileType() == TileType::Empty) { continue; }
		LOG_DEBUG << "\n[DFS] starting dfs for move at x=" << m.x
		          << " y=" << m.y << "\n";
		if (visited[m.y][m.x]) { continue; }

		bool tileTouchesExit = false;
		dfs(m.x, m.y, tileTouchesExit, visited);

		if (!tileTouchesExit) {
			LOG_DEBUG
			  << "move is false because a tile does not touch the exit\n";
			return false;
		}
	}

	return true;
}

bool Gameboard::validateMoves(const std::array<Move, 5> &moves)
{
	std::unordered_set<long long> seen;

	for (Move m : moves) {
		if (m.tile.getTileType() == TileType::Empty) { continue; }
		long long key = (static_cast<long long>(m.x) << 32) | (unsigned int)m.y;
		if (!seen.insert(key).second) {
			LOG_DEBUG << "Duplicate move\n";
			return false;
		}


		assert(m.x >= 0 && m.x < gameboardSize);
		assert(m.y >= 0 && m.y < gameboardSize);

		if (gameboard[m.y][m.x].getTileType() != TileType::Empty) {
			LOG_DEBUG << "Attempted to place tile on non-empty tile\n";
			return false;
		}
	}

	applyMoves(moves);
	bool valid = isConnected(moves);
	unapplyMoves(moves);

	return valid;
}

void Gameboard::applyMoves(const std::array<Move, 5> &moves)
{
	for (int i = 0; i < 5; i++) {
		if (moves[i].tile.getTileType() == TileType::Empty) { continue; }
		gameboard[moves[i].y][moves[i].x] = moves[i].tile;
	}
}

void Gameboard::unapplyMoves(const std::array<Move, 5> &moves)
{
	for (int i = 0; i < 5; i++) {
		if (moves[i].tile.getTileType() == TileType::Empty) { continue; }
		gameboard[moves[i].y][moves[i].x] = Tile();
	}
}
