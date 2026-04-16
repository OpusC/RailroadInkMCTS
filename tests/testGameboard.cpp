
#include "Gameboard.h"
#include "Tiles.h"
#include <array>
#include <gtest/gtest.h>

TEST(GameboardTest, ConstructorInitializesBoardAsEmptyTiles)
{
	Gameboard g = Gameboard();

	auto gameboard = g.getGameboard();

	for (int x = 0; x < gameboardSize; x++) {
		for (int y = 0; y < gameboardSize; y++) {
			ASSERT_EQ(TileType::Empty, gameboard[y][x].getTileType());
		}
	}
}

TEST(GameboardTest, ExitTileConnectionsAreValid)
{
	Gameboard g = Gameboard();

	std::array<Move, 5> moves = std::array<Move, 5>();

	Move m0{ Tile(TileType::StraightRoad, Rotation::Ninety), 0, 3 };
	Move m1{ Tile(TileType::StraightRoad, Rotation::Ninety), 6, 3 };
	Move m2{ Tile(TileType::StraightRoad, Rotation::Zero), 1, 0 };
	Move m3{ Tile(TileType::StraightRoad, Rotation::Zero), 5, 0 };

	moves[0] = m0;
	moves[1] = m1;
	moves[2] = m2;
	moves[3] = m3;

	bool isMoveValid = g.validateMoves(moves);
	ASSERT_EQ(true, isMoveValid);
};

TEST(GameboardTest, FailWhenNoTilesTouchExit)
{
	Gameboard g;

	Move m0{ Tile(TileType::StraightRail, Rotation::Zero), 2, 2 };
	Move m1{ Tile(TileType::StraightRail, Rotation::Zero), 3, 2 };
	Move m2{ Tile(TileType::StraightRail, Rotation::Zero), 2, 3 };
	Move m3{ Tile(TileType::StraightRail, Rotation::Zero), 3, 3 };

	std::array<Move, 5> moves = { m0, m1, m2, m3 };

	bool isMoveValid = g.validateMoves(moves);

	ASSERT_FALSE(isMoveValid);
}


TEST(GameboardTest, validMovesForCurvedRails)
{
	Gameboard g = Gameboard();
	std::array<Move, 5> moves = std::array<Move, 5>();

	Move m0{ Tile(TileType::StraightRail, Rotation::Zero), 3, 0 };
	Move m1{ Tile(TileType::StraightRail, Rotation::Zero), 3, 1 };
	Move m2{ Tile(TileType::CurvedRail, Rotation::Zero), 3, 2 };
	Move m3{ Tile(TileType::StraightRail, Rotation::Ninety), 4, 2 };

	moves = { m0, m1, m2, m3 };
	ASSERT_TRUE(g.validateMoves(moves));
}

TEST(GameboardTest, SingleIsolatedTileRestAreValidShouldFail)
{

	Gameboard g = Gameboard();

	std::array<Move, 5> moves;

	Move m0{ Tile(TileType::StraightRail, Rotation::Zero), 3, 3 };
	Move m1{ Tile(TileType::StraightRail, Rotation::Zero), 4, 4 };
	Move m2{ Tile(TileType::StraightRail, Rotation::Zero), 5, 5 };
	Move m3{ Tile(TileType::StraightRail, Rotation::Zero), 6, 6 };

	moves = { m0, m1, m2, m3 };

	ASSERT_FALSE(g.validateMoves(moves));
}

TEST(GameboardTest, ValidateMovesUsesBoardState)
{
	Gameboard g = Gameboard();


	std::array<Move, 5> firstMoves = { Move{ Tile(TileType::StraightRail, Rotation::Zero), 3, 0 },
		Move{ Tile(TileType::StraightRail, Rotation::Zero), 3, 1 },
		Move{ Tile(TileType::StraightRail, Rotation::Zero), 3, 2 },
		Move{ Tile(TileType::StraightRail, Rotation::Zero), 3, 3 } };

	ASSERT_TRUE(g.validateMoves(firstMoves));
	g.applyMoves(firstMoves);

	std::array<Move, 5> secondMoves = { Move{ Tile(TileType::StraightRail, Rotation::Zero), 3, 4 },
		Move{ Tile(TileType::CurvedRail, Rotation::Zero), 3, 5 },
		Move{ Tile(TileType::StraightRail, Rotation::Ninety), 4, 5 },
		Move{ Tile(TileType::StraightRail, Rotation::Ninety), 5, 5 } };

	ASSERT_TRUE(g.validateMoves(secondMoves));
}

TEST(GameboardTest, TilesTouchingOtherTilesConnectedToExitAreValid)
{
	Gameboard g = Gameboard();

	std::array<Move, 5> moves = std::array<Move, 5>();

	Move m0{ Tile(TileType::StraightRail, Rotation::Zero), 3, 0 };
	Move m1{ Tile(TileType::StraightRail, Rotation::Zero), 3, 1 };
	Move m2{ Tile(TileType::StraightRail, Rotation::Zero), 3, 2 };
	Move m3{ Tile(TileType::StraightRail, Rotation::Zero), 3, 3 };

	moves[0] = m0;
	moves[1] = m1;
	moves[2] = m2;
	moves[3] = m3;

	bool isMoveValid = g.validateMoves(moves);
	ASSERT_EQ(true, isMoveValid);
};

TEST(GameboardTest, FirstMoveShouldFailIfNotConnectedToExitWithWrongRotation)
{

	Gameboard g = Gameboard();

	std::array<Move, 5> moves = std::array<Move, 5>();

	Move m0{ Tile(TileType::StraightRoad, Rotation::Zero), 0, 3 };
	Move m1{ Tile(TileType::StraightRoad, Rotation::Zero), 6, 3 };
	Move m2{ Tile(TileType::StraightRoad, Rotation::Ninety), 1, 0 };
	Move m3{ Tile(TileType::StraightRoad, Rotation::Ninety), 6, 0 };

	moves[0] = m0;
	moves[1] = m1;
	moves[2] = m2;
	moves[3] = m3;

	bool isMoveValid = g.validateMoves(moves);
	ASSERT_EQ(false, isMoveValid);
}

TEST(GameboardTest, FirstMoveShouldFailIfNotConnectedToExit)
{

	Gameboard g = Gameboard();

	std::array<Move, 5> moves = std::array<Move, 5>();

	Move m0{ Tile(TileType::StraightRail, Rotation::Zero), 2, 2 };
	Move m1{ Tile(TileType::StraightRail, Rotation::Zero), 6, 3 };
	Move m2{ Tile(TileType::StraightRail, Rotation::Ninety), 1, 0 };
	Move m3{ Tile(TileType::StraightRail, Rotation::Ninety), 6, 0 };

	moves[0] = m0;
	moves[1] = m1;
	moves[2] = m2;
	moves[3] = m3;

	bool isMoveValid = g.validateMoves(moves);
	ASSERT_EQ(false, isMoveValid);
}

TEST(GameboardTest, MoveShouldNotBeAllowedOnSameTileAsAnotherMove)
{
	Gameboard g = Gameboard();

	std::array<Move, 5> moves = std::array<Move, 5>();

	Move m0{ Tile(TileType::StraightRail, Rotation::Ninety), 0, 3 };
	Move m1{ Tile(TileType::StraightRail, Rotation::Zero), 6, 3 };
	Move m2{ Tile(TileType::CurvedRail, Rotation::Ninety), 0, 3 };
	Move m3{ Tile(TileType::StraightRail, Rotation::Ninety), 6, 0 };

	moves[0] = m0;
	moves[1] = m1;
	moves[2] = m2;
	moves[3] = m3;

	bool isMoveValid = g.validateMoves(moves);
	ASSERT_EQ(false, isMoveValid);
};

TEST(GameboardTest, ExitTileConnectionsArePlacedOnBoard)
{
	Gameboard g = Gameboard();

	std::array<Move, 5> moves = std::array<Move, 5>();

	Move m0{ Tile(TileType::StraightRail, Rotation::Zero), 0, 3 };
	Move m1{ Tile(TileType::StraightRail, Rotation::Zero), 6, 3 };
	Move m2{ Tile(TileType::StraightRail, Rotation::Ninety), 1, 0 };
	Move m3{ Tile(TileType::StraightRail, Rotation::Ninety), 6, 0 };

	moves[0] = m0;
	moves[1] = m1;
	moves[2] = m2;
	moves[3] = m3;

	g.applyMoves(moves);

	ASSERT_EQ(m0.tile, g.getGameboard()[3][0]);
	ASSERT_EQ(m1.tile, g.getGameboard()[3][6]);
	ASSERT_EQ(m2.tile, g.getGameboard()[0][1]);
	ASSERT_EQ(m3.tile, g.getGameboard()[0][6]);
};

TEST(GameboardTest, GetExitTile)
{
	Gameboard g = Gameboard();
	ASSERT_EQ(Tile(TileType::StraightRail, Rotation::Ninety), g.getTile(-1, 1));
	ASSERT_EQ(true, g.getTile(-1, 1).isConnectedToExit);

	ASSERT_EQ(Tile(TileType::StraightRoad, Rotation::Zero), g.getTile(1, -1));
	ASSERT_EQ(true, g.getTile(1, -1).isConnectedToExit);
}

TEST(GameboardTest, GetEdgeTile)
{
	Gameboard g = Gameboard();
	ASSERT_EQ(false, g.getTile(-1, 2).isConnectedToExit);

	ASSERT_EQ(false, g.getTile(2, -1).isConnectedToExit);
}

TEST(BitwiseTest, And)
{
	ASSERT_TRUE(0b0100 & 0b0100);
	ASSERT_FALSE(0b1000 & 0b0100);
	ASSERT_FALSE(0b0000 & 0b0000);
}

TEST(TestArrayInitialization, FalseInit)
{
	std::array<std::array<bool, gameboardSize>, gameboardSize> visited = {};
	for (std::array<bool, gameboardSize> row : visited) {
		for (bool b : row) {
			ASSERT_EQ(false, b);
		}
	}
}
