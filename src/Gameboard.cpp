#include "Gameboard.h"
#include "Tiles.h"
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <unordered_set>
#include <utility>


Gameboard::Gameboard()
{
	for (int x = 0; x < gameboard_size; x++) {
		for (int y = 0; y < gameboard_size; y++) {
			gameboard[y][x] = Tile(TileType::EMPTY, Rotation::NONE, false);
		}
	}
}

Tile Gameboard::getTile(int x, int y) const
{
	// --- Exits ---
	if (y == gameboard_size || y == -1) {
		if (x == 1 || x == 5) return Tile(TileType::STRAIGHT_ROAD, Rotation::NONE, true);
		if (x == 3) return Tile(TileType::STRAIGHT_RAIL, Rotation::NONE, true);
	}

	if (x == -1 || x == gameboard_size) {
		if (y == 1 || y == 5) return Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY, true);
		if (y == 3) return Tile(TileType::STRAIGHT_ROAD, Rotation::NINETY, true);
	}

	// --- Edge-adjacent but NOT exits -> EMPTY ---
	if ((y == -1 || y == gameboard_size) && (0 <= x && x < gameboard_size))
		return Tile(TileType::EMPTY, Rotation::NONE, false);

	if ((x == -1 || x == gameboard_size) && (0 <= y && y < gameboard_size))
		return Tile(TileType::EMPTY, Rotation::NONE, false);

	// --- Out of bounds and not an exit or adjacent to edge ---
	assert(x >= 0 && x < gameboard_size);
	assert(y >= 0 && y < gameboard_size);

	return gameboard[y][x];
}

const uint8_t up_mask = 0b1000;
const uint8_t right_mask = 0b0100;
const uint8_t down_mask = 0b0010;
const uint8_t left_mask = 0b0001;
bool Gameboard::tilesConnect(Tile t1, Tile t2, int direction) const
{
	std::cout << "in tileConnect\n";
	assert(direction >= 0 and direction < 4);

	std::cout << "in tileConnect\n";
	bool res = false;

	switch (direction) {
	case 0: {
		std::cout << "checking up connection\n";
		res = (t1.getRails() & up_mask && t2.getRails() & down_mask)
		      || (t1.getRoads() & up_mask && t2.getRoads() & down_mask);
		break;
	}
	case 1: {
		std::cout << "checking right connection\n";
		res = (t1.getRails() & right_mask && t2.getRails() & left_mask)
		      || (t1.getRoads() & right_mask && t2.getRoads() & left_mask);
		break;
	}
	case 2: {
		std::cout << "checking down connection\n";
		res = (t1.getRails() & down_mask && t2.getRails() & up_mask)
		      || (t1.getRoads() & down_mask && t2.getRoads() & up_mask);
		break;
	}
	case 3: {
		std::cout << "checking left connection\n";
		res = (t1.getRails() & left_mask && t2.getRails() & right_mask)
		      || (t1.getRoads() & left_mask && t2.getRoads() & right_mask);
		break;
	}
	}

	std::cout << "  Tile connected: " << res << "\n";
	return res;
}

void Gameboard::dfs(int x,
  int y,
  bool &tileTouchesExit,
  std::array<std::array<bool, gameboard_size>, gameboard_size> &visited)
{
	Tile tile = getTile(x, y);

	if (tile.getTileType() == TileType::EMPTY) { return; }

	std::cout << "Visiting tile at x=" << x << " y=" << y << "\n";

	// Virtual exit tiles
	if (tile.isConnectedToExit) {
		std::cout << "tile at x=" << x << " y=" << y << " is an exit!\n";
		tileTouchesExit = true;
		return;
	}

	if (visited[y][x]) {
		std::cout << "tile has already been visted; returning\n";
		return;
	}
	visited[y][x] = true;


	const int dx[] = { 0, 1, 0, -1 };
	const int dy[] = { -1, 0, 1, 0 };

	for (int i = 0; i < 4; i++) {
		std::cout << "in for loop iteration " << i << "\n";
		int nx = x + dx[i];
		int ny = y + dy[i];

		Tile neighbour = getTile(nx, ny);

		std::cout << "checking nx=" << nx << " ny=" << ny << "\n";
		if (tilesConnect(tile, neighbour, i)) {
			dfs(nx, ny, tileTouchesExit, visited);
			if (tileTouchesExit) {
				std::cout << "Found an exit! Marking current tile as connected to exit\n";
				if ((x >= 0 && x < gameboard_size) && (y >= 0 && y < gameboard_size)) {
					gameboard[y][x].isConnectedToExit = true;
				}
				return;
			}
		}
	}
}

bool Gameboard::isConnected(std::array<Move, 4> moves)
{
	std::cout << "inside isConnected method\n";
	// create 7x7 array
	std::array<std::array<bool, gameboard_size>, gameboard_size> visited = {};


	for (Move m : moves) {
		std::cout << "\n[DFS] starting dfs for move at x=" << m.x << " y=" << m.y << "\n";
		if (visited[m.y][m.x]) { continue; }

		bool tileTouchesExit = false;
		dfs(m.x, m.y, tileTouchesExit, visited);

		if (!tileTouchesExit) {
			std::cout << "move is false because a tile does not touch the exit\n";
			return false;
		}
	}

	return true;
}

bool Gameboard::validateMoves(const std::array<Move, 4> &moves)
{
	std::unordered_set<long long> seen;

	for (Move m : moves) {
		long long key = (static_cast<long long>(m.x) << 32) | (unsigned int)m.y;
		if (!seen.insert(key).second) {
			std::cout << "Duplicate move\n";
			return false;
		}


		assert(m.x >= 0 && m.x < gameboard_size);
		assert(m.y >= 0 && m.y < gameboard_size);

		if (gameboard[m.y][m.x].getTileType() != TileType::EMPTY) {
			std::cout << "Attempted to place tile on non-empty tile\n";
			return false;
		}
	}

	applyMoves(moves);
	bool valid = isConnected(moves);
	unapplyMoves(moves);

	return valid;
}

void Gameboard::applyMoves(const std::array<Move, 4> &moves)
{
	for (int i = 0; i < 4; i++) {
		gameboard[moves[i].y][moves[i].x] = moves[i].tile;
	}
}

void Gameboard::unapplyMoves(const std::array<Move, 4> &moves)
{
	for (int i = 0; i < 4; i++) {
		gameboard[moves[i].y][moves[i].x] = Tile();
	}
}
