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
			gameboard[y][x] = Tile(TileType::EMPTY, Rotation::NONE);
		}
	}
}

Tile Gameboard::getTile(int x, int y) const
{
	// --- Exits ---
	if (y == gameboard_size || y == -1) {
		if (x == 1 || x == 5) return Tile(TileType::STRAIGHT_ROAD, Rotation::NONE);
		if (x == 3) return Tile(TileType::STRAIGHT_RAIL, Rotation::NONE);
	}

	if (x == -1 || x == gameboard_size) {
		if (y == 1 || y == 5) return Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY);
		if (y == 3) return Tile(TileType::STRAIGHT_ROAD, Rotation::NINETY);
	}

	// --- Edge-adjacent but NOT exits -> EMPTY ---
	if ((y == -1 || y == gameboard_size) && (0 <= x && x < gameboard_size))
		return Tile(TileType::EMPTY, Rotation::NONE);

	if ((x == -1 || x == gameboard_size) && (0 <= y && y < gameboard_size))
		return Tile(TileType::EMPTY, Rotation::NONE);

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
	assert(direction >= 0 and direction < 4);

	switch (direction) {
	case 1: {
		return (t1.getRails() & t2.getRails() & up_mask)
		       || (t1.getRoads() & t2.getRoads() & up_mask);
	}
	case 2: {
		return (t1.getRails() & t2.getRails() & right_mask)
		       || (t1.getRoads() & t2.getRoads() & right_mask);
	}
	case 3: {
		return (t1.getRails() & t2.getRails() & down_mask)
		       || (t1.getRoads() & t2.getRoads() & down_mask);
	}
	case 4: {
		return (t1.getRails() & t2.getRails() & left_mask)
		       || (t1.getRoads() & t2.getRoads() & left_mask);
	}
	}

	return false;
}

void Gameboard::dfs(Tile tile,
  int x,
  int y,
  bool &tileTouchesExit,
  std::array<std::array<bool, gameboard_size>, gameboard_size> &visited) const
{
	if (visited[x][y]) { return; }
	visited[y][x] = true;

	// TODO: try to prove if this early return is correct
	if (touchesExit[x][y]) { tileTouchesExit = true; }

	const int dx[] = { 0, 1, 0, -1 };
	const int dy[] = { -1, 0, 1, 0 };

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && nx < gameboard_size && ny >= 0 && ny < gameboard_size) {
			// continue dfs
			if (tilesConnect(tile, getTile(nx, ny), i)) {
				bool newTileTouchesExit;
				dfs(getTile(nx, ny), nx, ny, newTileTouchesExit, visited);
				// continue dfs?
			}
		}
	}
}

bool Gameboard::isConnected(std::array<Move, 4> moves) const
{
	// create 7x7 array
	std::array<std::array<bool, gameboard_size>, gameboard_size> visited;

	// get an array of all the exits
	std::array<Tile, 12> exits;

	for (Move m : moves) {
		if (visited[m.y][m.x]) { continue; }

		bool tileTouchesExit;
		dfs(m.tile, m.x, m.y, tileTouchesExit, visited);

		if (!tileTouchesExit) { return false; }
	}

	return true;

	/* --- DFS pseudocode ---
	 *
	 * 	procedure DFS(G, v) is
	 * 	    label v as discovered
	 * 	    for all directed edges from v to w that are in G.adjacentEdges(v) do
	 * 		if vertex w is not labeled as discovered then
	 * 		    recursively call DFS(G, w)
	 */

	/* --- DFS(int x, int y, bool visited[][], &tileTouchesExit, touchesExit[][])
	 * visited[y][x] = true;
	 *
	 * if (touchesExit[y][x]) tileTouchesExit = true;
	 *
	 * const dx = {0, 1, 0, -1}
	 * const dy = {-1, 0, 1, 0}
	 *
	 * for dir in range(4):
	 *	int nx = x + dx[dir];
	 *	int ny = y + dy[dir];
	 *	# check nx and ny are in bounds of gameboard
	 *
	 *	if ()
	 *
	 *
	 *
	 *
	 */
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

		if (gameboard[m.x][m.y].getTileType() != TileType::EMPTY) {

			std::cout << "Attempted to place tile on non-empty tile\n";
			return false;
		}
	}

	if (!isConnected(moves)) {
		return false;
	} else {
		return true;
	}
}

void Gameboard::applyMoves(const std::array<Move, 4> &moves)
{
	for (int i = 0; i < 4; i++) {
		gameboard[moves[i].y][moves[i].x] = moves[i].tile;
	}
}
