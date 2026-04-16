#include "Gameboard.h"
#include "Debug.h"
#include "Tiles.h"
#include <array>
#include <cassert>
#include <cstdint>
#include <unordered_set>
#include <utility>


Gameboard::Gameboard()
{
	for (int x = 0; x < gameboardSize; x++) {
		for (int y = 0; y < gameboardSize; y++) {
			gameboard[y][x] = Tile(TileType::Empty, Rotation::Zero, false);
		}
	}
}

Tile Gameboard::getTile(int x, int y) const
{
	// --- Exits ---
	if (y == gameboardSize || y == -1) {
		if (x == 1 || x == 5)
			return Tile(TileType::StraightRoad, Rotation::Zero, true);
		if (x == 3) return Tile(TileType::StraightRail, Rotation::Zero, true);
	}

	if (x == -1 || x == gameboardSize) {
		if (y == 1 || y == 5)
			return Tile(TileType::StraightRail, Rotation::Ninety, true);
		if (y == 3) return Tile(TileType::StraightRoad, Rotation::Ninety, true);
	}

	// --- Edge-adjacent but NOT exits -> Empty ---
	if ((y == -1 || y == gameboardSize) && (0 <= x && x < gameboardSize))
		return Tile(TileType::Empty, Rotation::Zero, false);

	if ((x == -1 || x == gameboardSize) && (0 <= y && y < gameboardSize))
		return Tile(TileType::Empty, Rotation::Zero, false);

	// --- Out of bounds and not an exit or adjacent to edge ---
	assert(x >= 0 && x < gameboardSize);
	assert(y >= 0 && y < gameboardSize);

	return gameboard[y][x];
}

bool Gameboard::isConnected(std::array<Move, 5> moves)
{
	LOG_DEBUG << "inside isConnected method\n";
	// create 7x7 array
	std::array<std::array<bool, gameboardSize>, gameboardSize> visited = {};


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
