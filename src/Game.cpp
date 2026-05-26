#include "Game.h"
#include "Gameboard.h"
#include <array>
#include <random>

// Each die is represented as its 6 faces (with repeats where the physical
// die has duplicate faces).
static const std::array<TileType, 6> routeDie = { StraightRail,
	CurvedRail,
	TRail,
	StraightRoad,
	CurvedRoad,
	TRoad };

static const std::array<TileType, 6> junctionDie = { TRail,
	TRail,
	TRoad,
	TRoad,
	RoadToRail,
	CurvedRoadToRail };

static const std::array<TileType, 6> overpassDie = { RoadRailUnderpass,
	TRail,
	TRoad,
	StraightRail,
	StraightRoad,
	CurvedRail };

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
