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

Game::Game(Gameboard gameboard)
  : gameboard(gameboard), turn(0), specialTilesUsed{}
{}
