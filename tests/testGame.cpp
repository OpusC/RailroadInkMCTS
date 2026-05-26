#include "BoardExit.h"
#include "Game.h"
#include "Gameboard.h"
#include <gtest/gtest.h>
#include <random>

Gameboard createGameboard()
{
	Gameboard gameboard = Gameboard(7, std::vector<BoardExit>{});
	return gameboard;
}

Game createGame()
{
	Gameboard gameboard = Gameboard(7, std::vector<BoardExit>{});

	std::mt19937 rng = std::mt19937(42);
	Game game = Game(createGameboard(), rng);
	return game;
}

bool isRouteFace(TileType t)
{
	return t == TileType::StraightRail || t == TileType::CurvedRail
	       || t == TileType::TRail || t == TileType::StraightRoad
	       || t == TileType::CurvedRoad || t == TileType::TRoad;
}

bool isSpecialFace(TileType t)
{
	return t == TileType::RoadRailUnderpass || t == TileType::RoadToRail
	       || t == TileType::CurvedRoadToRail;
}

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

TEST(GameTest, ConstructorInitializesProperly)
{
	std::mt19937 rng = std::mt19937(42);
	Game game = Game(createGameboard(), rng);

	EXPECT_EQ(game.getTurnNumber(), 0);
	EXPECT_EQ(game.getNumberOfSpecialTilesUsed(), 0);
}

TEST(GameTest, RollDiceProducesDiceRoll)
{
	Game game = createGame();
	DiceRoll roll = game.rollDice();
	EXPECT_TRUE(isRouteFace(roll.dice1));
	EXPECT_TRUE(isRouteFace(roll.dice2));
	EXPECT_TRUE(isRouteFace(roll.dice3));
	EXPECT_TRUE(isSpecialFace(roll.dice4));
}
