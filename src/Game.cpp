#include "Game.h"
#include "Gameboard.h"
#include <array>

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

// TODO: complete this method
void Game::applyTurn(const TurnMoves &moves) { this->turn += 1; };
