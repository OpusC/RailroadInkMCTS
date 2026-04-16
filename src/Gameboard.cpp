#include "Debug.h"
#include "Gameboard.h"
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
		if (x == 1 || x == 5) return Tile(TileType::StraightRoad, Rotation::Zero, true);
		if (x == 3) return Tile(TileType::StraightRail, Rotation::Zero, true);
	}

	if (x == -1 || x == gameboardSize) {
		if (y == 1 || y == 5) return Tile(TileType::StraightRail, Rotation::Ninety, true);
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

const uint8_t upMask = 0b1000;
const uint8_t rightMask = 0b0100;
const uint8_t downMask = 0b0010;
const uint8_t leftMask = 0b0001;
bool Gameboard::tilesConnect(Tile t1, Tile t2, int direction) const
{
	LOG_DEBUG << "in tileConnect\n";
	assert(direction >= 0 and direction < 4);

	LOG_DEBUG << "in tileConnect\n";
	bool res = false;

	switch (direction) {
	case 0: {
		LOG_DEBUG << "checking up connection\n";
		res = (t1.getRails() & upMask && t2.getRails() & downMask)
		      || (t1.getRoads() & upMask && t2.getRoads() & downMask);
		break;
	}
	case 1: {
		LOG_DEBUG << "checking right connection\n";
		res = (t1.getRails() & rightMask && t2.getRails() & leftMask)
		      || (t1.getRoads() & rightMask && t2.getRoads() & leftMask);
		break;
	}
	case 2: {
		LOG_DEBUG << "checking down connection\n";
		res = (t1.getRails() & downMask && t2.getRails() & upMask)
		      || (t1.getRoads() & downMask && t2.getRoads() & upMask);
		break;
	}
	case 3: {
		LOG_DEBUG << "checking left connection\n";
		res = (t1.getRails() & leftMask && t2.getRails() & rightMask)
		      || (t1.getRoads() & leftMask && t2.getRoads() & rightMask);
		break;
	}
	}

	LOG_DEBUG << "  Tile connected: " << res << "\n";
	return res;
}

void Gameboard::dfs(int x,
  int y,
  bool &tileTouchesExit,
  std::array<std::array<bool, gameboardSize>, gameboardSize> &visited)
{
	Tile tile = getTile(x, y);

	if (tile.getTileType() == TileType::Empty) { return; }

	LOG_DEBUG << "Visiting tile at x=" << x << " y=" << y << "\n";

	// Virtual exit tiles
	if (tile.isConnectedToExit) {
		LOG_DEBUG << "tile at x=" << x << " y=" << y << " is an exit!\n";
		tileTouchesExit = true;
		return;
	}

	if (visited[y][x]) {
		LOG_DEBUG << "tile has already been visted; returning\n";
		return;
	}
	visited[y][x] = true;


	const int dx[] = { 0, 1, 0, -1 };
	const int dy[] = { -1, 0, 1, 0 };

	for (int i = 0; i < 4; i++) {
		LOG_DEBUG << "in for loop iteration " << i << "\n";
		int nx = x + dx[i];
		int ny = y + dy[i];

		Tile neighbour = getTile(nx, ny);

		LOG_DEBUG << "checking nx=" << nx << " ny=" << ny << "\n";
		if (tilesConnect(tile, neighbour, i)) {
			dfs(nx, ny, tileTouchesExit, visited);
			if (tileTouchesExit) {
				LOG_DEBUG << "Found an exit! Marking current tile as connected to exit\n";
				if ((x >= 0 && x < gameboardSize) && (y >= 0 && y < gameboardSize)) {
					gameboard[y][x].isConnectedToExit = true;
				}
				return;
			}
		}
	}
}

bool Gameboard::isConnected(std::array<Move, 5> moves)
{
	LOG_DEBUG << "inside isConnected method\n";
	// create 7x7 array
	std::array<std::array<bool, gameboardSize>, gameboardSize> visited = {};


	for (Move m : moves) {
		if (m.tile.getTileType() == TileType::Empty) { continue; }
		LOG_DEBUG << "\n[DFS] starting dfs for move at x=" << m.x << " y=" << m.y << "\n";
		if (visited[m.y][m.x]) { continue; }

		bool tileTouchesExit = false;
		dfs(m.x, m.y, tileTouchesExit, visited);

		if (!tileTouchesExit) {
			LOG_DEBUG << "move is false because a tile does not touch the exit\n";
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
