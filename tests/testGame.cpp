#include "BoardExit.h"
#include "Game.h"
#include "Gameboard.h"
#include <gtest/gtest.h>
#include <random>

// TODO: sanity test harness that plays a game
// Game g(board, seed);
//
// while (!g.isGameOver()) {
//     auto roll = g.rollDice();
//     auto turns = g.generateLegalTurns(roll);
//
//     assert(!turns.empty());
//
//     g.applyTurn(turns[0]); // or random
// }

Gameboard createGameboard()
{
	Gameboard gameboard = Gameboard(7, std::vector<BoardExit>{});
	return gameboard;
}

Game createGame()
{
	Gameboard gameboard = Gameboard(7, std::vector<BoardExit>{});

	Game game = Game(createGameboard());
	return game;
}

// TODO: tile enum method owns this
bool isRouteFace(TileType t)
{
	return t == TileType::StraightRail || t == TileType::CurvedRail
	       || t == TileType::TRail || t == TileType::StraightRoad
	       || t == TileType::CurvedRoad || t == TileType::TRoad;
}

// TODO: tile enum method owns this
bool isSpecialFace(TileType t)
{
	return t == TileType::RoadRailUnderpass || t == TileType::RoadToRail
	       || t == TileType::CurvedRoadToRail;
}


TEST(GameTest, ConstructorInitializesProperly)
{
	Game game = Game(createGameboard());

	EXPECT_EQ(game.getTurnNumber(), 0);
}


TEST(GameTest, CanApplyTurn) { Game game = createGame(); }

TEST(GameTest, ApplyTurnIncrementsTurnCounter) { Game game = createGame(); }
