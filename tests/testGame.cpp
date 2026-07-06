#include "BoardExit.h"
#include "Game.h"
#include "Gameboard.h"
#include "Move.h"
#include <gtest/gtest.h>

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
	std::vector<BoardExit> exits{
		// Top edge (y=0)
		BoardExit{ 1, 0, Direction::Up, ConnectionType::Rail },
		BoardExit{ 3, 0, Direction::Up, ConnectionType::Road },
		BoardExit{ 5, 0, Direction::Up, ConnectionType::Rail },

		// Right edge (x=6)
		BoardExit{ 6, 1, Direction::Right, ConnectionType::Road },
		BoardExit{ 6, 3, Direction::Right, ConnectionType::Rail },
		BoardExit{ 6, 5, Direction::Right, ConnectionType::Road },

		// Bottom edge (y=6)
		BoardExit{ 1, 6, Direction::Down, ConnectionType::Rail },
		BoardExit{ 3, 6, Direction::Down, ConnectionType::Road },
		BoardExit{ 5, 6, Direction::Down, ConnectionType::Rail },

		// Left edge (x=0)
		BoardExit{ 0, 1, Direction::Left, ConnectionType::Road },
		BoardExit{ 0, 3, Direction::Left, ConnectionType::Rail },
		BoardExit{ 0, 5, Direction::Left, ConnectionType::Road },
	};

	Gameboard gameboard = Gameboard(7, exits);
	Game game = Game(gameboard);
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

TEST(GameTest, CanApplyTurn)
{
	Game game = createGame();
	Tile straightRoad = Tile(TileType::StraightRoad);
	TurnMoves moves = {
		Move{ straightRoad, 1, 1 },// connects to top exit at x=1, y=0
		Move{ straightRoad, 1, 5 },// connects to bottom exit at x=1, y=6
		Move{ straightRoad, 5, 1 },// connects to top exit at x=5, y=0
		Move{ straightRoad, 5, 5 },// connects to bottom exit at x=5, y=6
		std::nullopt
	};
	ASSERT_NO_FATAL_FAILURE(game.applyTurn(moves));
}

// TODO: write test
TEST(GameTest, ApplyTurnIncrementsTurnCounter)
{
	Game game = createGame();

	Tile straightRoad = Tile(TileType::StraightRoad);
	TurnMoves moves = {
		Move{ straightRoad, 1, 1 },// connects to top exit at x=1, y=0
		Move{ straightRoad, 1, 5 },// connects to bottom exit at x=1, y=6
		Move{ straightRoad, 5, 1 },// connects to top exit at x=5, y=0
		Move{ straightRoad, 5, 5 },// connects to bottom exit at x=5, y=6
		std::nullopt
	};

	game.applyTurn(moves);
	ASSERT_EQ(game.getTurnNumber(), 1);
}
