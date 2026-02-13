#include "Gameboard.h"
#include "Tiles.h"
#include <array>
#include <cassert>
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

	// test that the move is connected after placement? before placement?
	// Strategy: place the tiles, on each tile call a isConnected() method
	// if one is not connected, undo all by looping through the moves and
	// setting all the tiles with x and y coordinates back to TileType::Empty

	return true;
}

void Gameboard::applyMoves(const std::array<Move, 4> &moves)
{
	for (int i = 0; i < 4; i++) {
		gameboard[moves[i].y][moves[i].x] = moves[i].tile;
	}
}
