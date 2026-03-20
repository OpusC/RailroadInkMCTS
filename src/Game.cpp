#include "Game.h"
#include "Tiles.h"
#include <array>
#include <random>

// Each die is represented as its 6 faces (with repeats where the physical
// die has duplicate faces).
static const std::array<TileType, 6> ROUTE_DIE = {
	STRAIGHT_RAIL, CURVED_RAIL, T_RAIL, STRAIGHT_ROAD, CURVED_ROAD, T_ROAD
};

static const std::array<TileType, 6> JUNCTION_DIE = {
	T_RAIL, T_RAIL, T_ROAD, T_ROAD, ROAD_TO_RAIL, CURVED_ROAD_TO_RAIL
};

static const std::array<TileType, 6> OVERPASS_DIE = {
	ROAD_RAIL_UNDERPASS, T_RAIL, T_ROAD, STRAIGHT_RAIL, STRAIGHT_ROAD, CURVED_RAIL
};

Game::Game() : rng(std::random_device{}())
{
	gameboard = Gameboard();
	turn = 0;
	specialTileUsed.fill(false);
}

Game::Game(uint32_t seed) : rng(seed)
{
	gameboard = Gameboard();
	turn = 0;
	specialTileUsed.fill(false);
}

Game::Game(const Game &game) = default;
Game::Game(Game &&game) = default;

const std::array<TileType, 4> Game::rollDice()
{
	std::uniform_int_distribution<int> d6(0, 5);

	return {
		ROUTE_DIE[d6(rng)],
		ROUTE_DIE[d6(rng)],
		JUNCTION_DIE[d6(rng)],
		OVERPASS_DIE[d6(rng)],
	};
}
