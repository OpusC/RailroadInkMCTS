#include "BoardExit.h"
#include "Gameboard.h"
#include "TileEnums.h"
#include "Tiles.h"
#include <gtest/gtest.h>
#include <vector>

TEST(GameboardTest, ExitInitializationShouldNotAllowDuplicateOriginCoordinates)
{
	BoardExit exit1{ 0, 0, Direction::Up, ConnectionType::Rail };
	BoardExit exit2{ 0, 0, Direction::Left, ConnectionType::Road };
	std::vector<BoardExit> exits{ exit1, exit2 };

	ASSERT_DEATH(Gameboard g = Gameboard(4, exits), "");
}

TEST(GameboardTest, ConstructorInitializesBoardAsEmptyTiles)
{
	Gameboard g = Gameboard(7, std::vector<BoardExit>{});

	auto gameboard = g.getGameboard();

	for (int x = 0; x < g.getSize(); x++) {
		for (int y = 0; y < g.getSize(); y++) {
			ASSERT_EQ(TileType::Empty, g.getTile(x, y).getTileType());
		}
	}
}

TEST(GameboardTest, ConstructorPlacesExitTiles)
{
	int size = 7;
	BoardExit upRailExit{ 0, 0, Direction::Up, ConnectionType::Rail };
	BoardExit leftRoadExit{ 0, 2, Direction::Left, ConnectionType::Road };

	BoardExit rightRailExit{
		size - 1, 0, Direction::Right, ConnectionType::Rail
	};

	BoardExit downRoadExit{
		0, size - 1, Direction::Down, ConnectionType::Road
	};

	Gameboard g = Gameboard(size,
	  std::vector<BoardExit>{
	    upRailExit, leftRoadExit, rightRailExit, downRoadExit });

	auto gameboard = g.getGameboard();

	ASSERT_EQ(TileType::StraightRail, gameboard[0][1].getTileType());

	ASSERT_EQ(TileType::StraightRoad, gameboard[3][0].getTileType());

	ASSERT_EQ(TileType::StraightRail, gameboard[1][8].getTileType());

	ASSERT_EQ(TileType::StraightRoad, gameboard[8][1].getTileType());
}

TEST(GameboardTest, ExitTileConnectionsAreValid)
{
	BoardExit exit1{ 0, 0, Direction::Up, ConnectionType::Rail };
	BoardExit exit2{ 0, 2, Direction::Left, ConnectionType::Road };
	BoardExit exit3{ 4, 0, Direction::Up, ConnectionType::Road };
	BoardExit exit4{ 4, 2, Direction::Right, ConnectionType::Rail };
	std::vector<BoardExit> exits{ exit1, exit2, exit3, exit4 };

	Gameboard g = Gameboard(5, exits);

	const Tile &t1 = Tile(TileType::StraightRail, Rotation::Zero);
	const Tile &t2 = Tile(TileType::StraightRoad, Rotation::Ninety);
	const Tile &t3 = Tile(TileType::StraightRoad, Rotation::Zero);
	const Tile &t4 = Tile(TileType::StraightRail, Rotation::Ninety);
	Move m1{ t1, 0, 0 };
	Move m2{ t2, 0, 2 };
	Move m3{ t3, 4, 0 };
	Move m4{ t4, 4, 2 };


	ASSERT_EQ(true, g.isMoveValid(m1));
	ASSERT_EQ(true, g.isMoveValid(m2));
	ASSERT_EQ(true, g.isMoveValid(m3));
	ASSERT_EQ(true, g.isMoveValid(m4));
};

TEST(GameboardTest, FailWhenNoTilesTouchExit)
{

	BoardExit exit1{ 0, 0, Direction::Up, ConnectionType::Rail };
	BoardExit exit2{ 0, 2, Direction::Left, ConnectionType::Road };
	BoardExit exit3{ 4, 0, Direction::Up, ConnectionType::Road };
	BoardExit exit4{ 4, 2, Direction::Right, ConnectionType::Rail };
	std::vector<BoardExit> exits{ exit1, exit2, exit3, exit4 };

	Gameboard g = Gameboard(5, exits);

	const Tile &t1 = Tile(TileType::StraightRail, Rotation::Zero);
	const Tile &t2 = Tile(TileType::StraightRail, Rotation::Zero);
	const Tile &t3 = Tile(TileType::StraightRail, Rotation::Zero);
	const Tile &t4 = Tile(TileType::StraightRail, Rotation::Zero);

	Move m1{ t1, 1, 0 };
	Move m2{ t2, 1, 2 };
	Move m3{ t3, 4, 1 };
	Move m4{ t4, 4, 3 };


	ASSERT_EQ(false, g.isMoveValid(m1));
	ASSERT_EQ(false, g.isMoveValid(m2));
	ASSERT_EQ(false, g.isMoveValid(m3));
	ASSERT_EQ(false, g.isMoveValid(m4));
}


TEST(GameboardTest, validMovesForCurvedRailOnExit)
{

	BoardExit exit1{ 0, 0, Direction::Up, ConnectionType::Rail };
	std::vector<BoardExit> exits{ exit1 };

	Gameboard g = Gameboard(5, exits);

	Move m2{ Tile(TileType::CurvedRail, Rotation::Zero), 0, 2 };

	g.isMoveValid(m2);
}

TEST(GameboardTest, ApplyMoveUsesBoardState)
{
	BoardExit exit1{ 0, 0, Direction::Up, ConnectionType::Rail };
	std::vector<BoardExit> exits{ exit1 };

	Gameboard g = Gameboard(5, exits);

	Move m1{ Tile(TileType::CurvedRail, Rotation::Zero), 0, 0 };
	ASSERT_EQ(true, g.isMoveValid(m1));
	g.applyMove(m1);

	Move m2{ Tile(TileType::StraightRail, Rotation::Ninety), 1, 0 };
	ASSERT_EQ(true, g.isMoveValid(m2));
}

TEST(GameboardTest, ApplyMoveUsesBoardState2)
{
	BoardExit exit1{ 0, 1, Direction::Left, ConnectionType::Rail };
	std::vector<BoardExit> exits{ exit1 };

	Gameboard g = Gameboard(5, exits);

	Move m1{ Tile(TileType::StraightRail, Rotation::Ninety), 0, 1 };
	ASSERT_EQ(true, g.isMoveValid(m1));
	g.applyMove(m1);


	Move m2{ Tile(TileType::StraightRail, Rotation::Ninety), 1, 1 };
	ASSERT_EQ(true, g.isMoveValid(m2));
}


TEST(GameboardTest, MoveShouldFailWithIncorrectRotation)
{

	BoardExit exit1{ 0, 0, Direction::Up, ConnectionType::Rail };
	std::vector<BoardExit> exits{ exit1 };

	Gameboard g = Gameboard(5, exits);

	Move m1{ Tile(TileType::StraightRail, Rotation::Ninety), 0, 0 };
	ASSERT_EQ(false, g.isMoveValid(m1));
}

TEST(GameboardTest, ApplyMovePlacesTile)
{
	BoardExit exit1{ 0, 0, Direction::Up, ConnectionType::Rail };
	std::vector<BoardExit> exits{ exit1 };

	Gameboard g = Gameboard(5, exits);
	auto t1 = Tile(TileType::StraightRail, Rotation::Zero);
	Move m1{ t1, 0, 0 };
	ASSERT_EQ(true, g.isMoveValid(m1));
	g.applyMove(m1);

	ASSERT_EQ(t1, g.getGameboard()[1][1]);
};


TEST(GameboardTest, MoveShouldNotBeAllowedOnSameTileAsAnotherMove)
{
	BoardExit exit1{ 0, 0, Direction::Up, ConnectionType::Rail };
	std::vector<BoardExit> exits{ exit1 };

	Gameboard g = Gameboard(5, exits);

	Move m1{ Tile(TileType::StraightRail, Rotation::Zero), 0, 0 };
	ASSERT_EQ(true, g.isMoveValid(m1));
	g.applyMove(m1);

	Move m2{ Tile(TileType::StraightRail, Rotation::Zero), 0, 0 };
	ASSERT_EQ(false, g.isMoveValid(m2));
};

TEST(GameboardTest, MoveShouldNotCreateDeadEnd)
{
	BoardExit exit1{ 0, 1, Direction::Left, ConnectionType::Rail };
	BoardExit exit2{ 1, 0, Direction::Up, ConnectionType::Rail };
	std::vector<BoardExit> exits{ exit1, exit2 };

	Gameboard g = Gameboard(5, exits);

	Move m1{ Tile(TileType::StraightRail, Rotation::Ninety), 0, 1 };
	ASSERT_EQ(true, g.isMoveValid(m1));
	g.applyMove(m1);

	Move m2{ Tile(TileType::StraightRail, Rotation::Zero), 1, 0 };
	ASSERT_EQ(true, g.isMoveValid(m2));
	g.applyMove(m2);

	Move m3{ Tile(TileType::StraightRail, Rotation::Zero), 1, 1 };
	ASSERT_EQ(false, g.isMoveValid(m3));
};

TEST(GameboardTest, MoveShouldBeAllowedAsItDoesNotCreateDeadEnd)
{
	BoardExit exit1{ 0, 1, Direction::Left, ConnectionType::Rail };
	BoardExit exit2{ 1, 0, Direction::Up, ConnectionType::Rail };
	std::vector<BoardExit> exits{ exit1, exit2 };

	Gameboard g = Gameboard(5, exits);

	Move m1{ Tile(TileType::StraightRail, Rotation::Ninety), 0, 1 };
	ASSERT_EQ(true, g.isMoveValid(m1));
	g.applyMove(m1);

	Move m2{ Tile(TileType::StraightRail, Rotation::Zero), 1, 0 };
	ASSERT_EQ(true, g.isMoveValid(m2));
	g.applyMove(m2);

	Move m3{ Tile(TileType::CurvedRail, Rotation::TwoSeventy), 1, 1 };
	ASSERT_EQ(true, g.isMoveValid(m3));
};

TEST(GameboardTest, ShouldConnectTwoTiles)
{
	BoardExit exit{ 0, 1, Direction::Left, ConnectionType::Rail };
	std::vector<BoardExit> exits{ exit };

	Gameboard g = Gameboard(5, exits);


	Move m1{ Tile(TileType::StraightRail, Rotation::Ninety), 0, 1 };
	ASSERT_EQ(true, g.isMoveValid(m1));
	g.applyMove(m1);

	Move m2{ Tile(TileType::StraightRail, Rotation::Ninety), 1, 1 };
	ASSERT_EQ(true, g.isMoveValid(m2));
	g.applyMove(m2);

	Move m3{ Tile(TileType::CurvedRail, Rotation::OneEighty), 2, 1 };
	ASSERT_EQ(true, g.isMoveValid(m3));
};
