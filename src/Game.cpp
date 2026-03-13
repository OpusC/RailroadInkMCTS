#include "Game.h"
#include "Tiles.h"
#include <array>

Game::Game()
{
	gameboard = Gameboard();
	turn = 0;
}

const std::array<TileType, 4> Game::rollDice()
{
	std::array<TileType, 4> diceResult;

	diceResult[0] = TileType::CURVED_RAIL;
	diceResult[1] = TileType::STRAIGHT_ROAD;
	diceResult[2] = TileType::T_RAIL;
	diceResult[3] = TileType::CURVED_RAIL;

	return diceResult;
}
