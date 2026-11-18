#include "BoardExit.h"
#include "Game.h"
#include "Gameboard.h"
#include "Move.h"
#include <gtest/gtest.h>

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


TEST(GameTest, ConstructorAwaitsRoll)
{
	Game game = createGame();

	EXPECT_EQ(game.getTurnNumber(), 0);
	EXPECT_TRUE(game.isChanceNode());
	EXPECT_TRUE(game.legalActions().empty());
}

TEST(GameTest, PlacementConsumesADieWithoutEndingTheRound)
{
	Game game(
	  Gameboard(1, { BoardExit{ 0, 0, Direction::Up, ConnectionType::Road } }));
	game.applyAction(
	  DiceRoll{ StraightRoad, StraightRoad, StraightRoad, RoadToRail });
	EXPECT_THROW(game.applyAction(EndTurn{}), std::invalid_argument);

	const Move placement{ Tile(StraightRoad), 0, 0 };
	const auto actions = game.legalActions();
	int matchingPlacements = 0;
	for (const auto &action : actions) {
		const auto *move = std::get_if<Move>(&action);
		if (move && move->tile == placement.tile && move->x == 0
		    && move->y == 0) {
			++matchingPlacements;
		}
	}
	EXPECT_EQ(matchingPlacements, 1);

	Game simulation = game;
	simulation.applyAction(placement);
	EXPECT_EQ(simulation.getTurnNumber(), 0);
	EXPECT_THROW(simulation.applyAction(placement), std::invalid_argument);

	const auto remainingActions = simulation.legalActions();
	ASSERT_EQ(remainingActions.size(), 1);
	EXPECT_TRUE(std::holds_alternative<EndTurn>(remainingActions[0]));
	simulation.applyAction(EndTurn{});
	EXPECT_EQ(simulation.getTurnNumber(), 1);
	EXPECT_TRUE(simulation.isChanceNode());
	EXPECT_FALSE(game.isChanceNode());
	EXPECT_FALSE(game.isGameOver());
	EXPECT_NO_THROW(game.applyAction(placement));
}
