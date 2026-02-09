#include "Gameboard.h"
#include "Tiles.h"
#include <array>
#include <iostream>

Gameboard::Gameboard()
{
	for (int x = 0; x < gameboard_size; x++) {
		for (int y = 0; y < gameboard_size; y++) {
			gameboard[y][x] = Tile(TileType::ROAD_TO_RAIL, Rotation::NONE);
		}
	}
}

bool Gameboard::validateMoves(const std::array<Move, 4> &moves)
{
	for (Move m : moves) {
		if (gameboard[m.x][m.y].getTileType() != TileType::EMPTY) { return false; }
	}
	// I think I also have to check if any of the tiles have the same x y as each other?

	return true;
}

void Gameboard::applyMoves(const std::array<Move, 4> &moves)
{
	for (int i = 0; i < 4; i++) {
		gameboard[moves[i].y][moves[i].x] = moves[i].tile;
	}
}
