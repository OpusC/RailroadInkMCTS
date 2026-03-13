
#include "Gameboard.h"
#include "Tiles.h"
#include <array>
#include <gtest/gtest.h>

TEST(GameboardTest, ConstructorInitializesBoardAsEmptyTiles)
{
	Gameboard g = Gameboard();

	auto gameboard = g.getGameboard();

	for (int x = 0; x < gameboard_size; x++) {
		for (int y = 0; y < gameboard_size; y++) {
			ASSERT_EQ(TileType::EMPTY, gameboard[y][x].getTileType());
		}
	}
}

TEST(GameboardTest, ExitTileConnectionsAreValid)
{
	Gameboard g = Gameboard();

	std::array<Move, 4> moves = std::array<Move, 4>();

	Move m0{ Tile(TileType::STRAIGHT_ROAD, Rotation::NINETY), 0, 3 };
	Move m1{ Tile(TileType::STRAIGHT_ROAD, Rotation::NINETY), 6, 3 };
	Move m2{ Tile(TileType::STRAIGHT_ROAD, Rotation::NONE), 1, 0 };
	Move m3{ Tile(TileType::STRAIGHT_ROAD, Rotation::NONE), 5, 0 };

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

	Move m0{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 2, 2 };
	Move m1{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 2 };
	Move m2{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 2, 3 };
	Move m3{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 3 };

	std::array<Move, 4> moves = { m0, m1, m2, m3 };

	bool isMoveValid = g.validateMoves(moves);

	ASSERT_FALSE(isMoveValid);
}


TEST(GameboardTest, validMovesForCurvedRails)
{
	Gameboard g = Gameboard();
	std::array<Move, 4> moves = std::array<Move, 4>();

	Move m0{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 0 };
	Move m1{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 1 };
	Move m2{ Tile(TileType::CURVED_RAIL, Rotation::NONE), 3, 2 };
	Move m3{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 4, 2 };

	moves = { m0, m1, m2, m3 };
	ASSERT_TRUE(g.validateMoves(moves));
}

TEST(GameboardTest, SingleIsolatedTileRestAreValidShouldFail)
{

	Gameboard g = Gameboard();

	std::array<Move, 4> moves;

	Move m0{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 3 };
	Move m1{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 4, 4 };
	Move m2{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 5, 5 };
	Move m3{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 6, 6 };

	moves = { m0, m1, m2, m3 };

	ASSERT_FALSE(g.validateMoves(moves));
}

TEST(GameboardTest, ValidateMovesUsesBoardState)
{
	Gameboard g = Gameboard();


	std::array<Move, 4> firstMoves = { Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 0 },
		Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 1 },
		Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 2 },
		Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 3 } };

	ASSERT_TRUE(g.validateMoves(firstMoves));
	g.applyMoves(firstMoves);

	std::array<Move, 4> secondMoves = { Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 4 },
		Move{ Tile(TileType::CURVED_RAIL, Rotation::NONE), 3, 5 },
		Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 4, 5 },
		Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 5, 5 } };

	ASSERT_TRUE(g.validateMoves(secondMoves));
}

TEST(GameboardTest, TilesTouchingOtherTilesConnectedToExitAreValid)
{
	Gameboard g = Gameboard();

	std::array<Move, 4> moves = std::array<Move, 4>();

	Move m0{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 0 };
	Move m1{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 1 };
	Move m2{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 2 };
	Move m3{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 3 };

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

	std::array<Move, 4> moves = std::array<Move, 4>();

	Move m0{ Tile(TileType::STRAIGHT_ROAD, Rotation::NONE), 0, 3 };
	Move m1{ Tile(TileType::STRAIGHT_ROAD, Rotation::NONE), 6, 3 };
	Move m2{ Tile(TileType::STRAIGHT_ROAD, Rotation::NINETY), 1, 0 };
	Move m3{ Tile(TileType::STRAIGHT_ROAD, Rotation::NINETY), 6, 0 };

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

	std::array<Move, 4> moves = std::array<Move, 4>();

	Move m0{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 2, 2 };
	Move m1{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 6, 3 };
	Move m2{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 1, 0 };
	Move m3{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 6, 0 };

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

	std::array<Move, 4> moves = std::array<Move, 4>();

	Move m0{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 0, 3 };
	Move m1{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 6, 3 };
	Move m2{ Tile(TileType::CURVED_RAIL, Rotation::NINETY), 0, 3 };
	Move m3{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 6, 0 };

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

	std::array<Move, 4> moves = std::array<Move, 4>();

	Move m0{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 0, 3 };
	Move m1{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 6, 3 };
	Move m2{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 1, 0 };
	Move m3{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 6, 0 };

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
	ASSERT_EQ(Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), g.getTile(-1, 1));
	ASSERT_EQ(true, g.getTile(-1, 1).isConnectedToExit);

	ASSERT_EQ(Tile(TileType::STRAIGHT_ROAD, Rotation::NONE), g.getTile(1, -1));
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
	std::array<std::array<bool, gameboard_size>, gameboard_size> visited = {};
	for (std::array<bool, gameboard_size> row : visited) {
		for (bool b : row) {
			ASSERT_EQ(false, b);
		}
	}
}
