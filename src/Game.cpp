#include "Game.h"
#include "Gameboard.h"
#include <array>
#include <random>

static const std::array<TileType, 6> routeDie = { TileType::StraightRail,
	TileType::CurvedRail,
	TileType::TRail,
	TileType::StraightRoad,
	TileType::CurvedRoad,
	TileType::TRoad };

static const std::array<TileType, 6> specialDie = { TileType::RoadRailUnderpass,
	TileType::RoadRailUnderpass,
	TileType::RoadToRail,
	TileType::RoadToRail,
	TileType::CurvedRoadToRail,
	TileType::CurvedRoadToRail };

Game::Game(Gameboard gameboard, std::mt19937 rng)
  : gameboard(gameboard), rng(rng)
{
	turn = 0;
	specialTilesUsed = { false, false, false, false, false, false };
}

int Game::getNumberOfSpecialTilesUsed() const
{
	int count = 0;
	// for (bool used : specialTileUsed) {
	// 	if (used) count++;
	// }
	return count;// TODO: Stub
}

DiceRoll Game::rollDice()
{
	std::uniform_int_distribution<int> d6(0, 5);
	// Distribution and engine are separate - d6 defines the range, rng provides
	// the bits
	// Calling d6(rng) uses operator()
	// This is called a function object
	return { routeDie[d6(rng)],
		routeDie[d6(rng)],
		routeDie[d6(rng)],
		specialDie[d6(rng)] };
}
