
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

	Move m0{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 0, 3 };
	Move m1{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 6, 3 };
	Move m2{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 1, 0 };
	Move m3{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 6, 0 };

	moves[0] = m0;
	moves[1] = m1;
	moves[2] = m2;
	moves[3] = m3;

	bool isMoveValid = g.validateMoves(moves);
	ASSERT_EQ(true, isMoveValid);
};

TEST(GameboardTest, FirstMoveShouldFailIfNotConnectedToExitWithCorrectRotation)
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


	ASSERT_EQ(m0.tile, g.getGameboard()[0][3]);
};
