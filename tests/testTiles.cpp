#include "Tiles.h"
#include <gtest/gtest.h>

TEST(TileTest, NoRotation)
{
	Tile t = Tile(TileType::CURVED_RAIL, Rotation::NONE);
	EXPECT_EQ(0b1100, t.getRails());
}

TEST(TileTest, NinetyRotation)
{
	Tile t = Tile(TileType::CURVED_RAIL, Rotation::NINETY);
	EXPECT_EQ(0b0110, t.getRails());
}

TEST(TileTest, OneEightyRotation)
{
	Tile t = Tile(TileType::CURVED_RAIL, Rotation::ONE_EIGHTY);
	EXPECT_EQ(0b0011, t.getRails());
}

TEST(TileTest, TwoSeventyRotation)
{
	Tile t = Tile(TileType::CURVED_RAIL, Rotation::TWO_SEVENTY);
	EXPECT_EQ(0b1001, t.getRails());
}

TEST(TileTest, GetTileType)
{
	Tile t = Tile(TileType::CURVED_RAIL, Rotation::TWO_SEVENTY);
	EXPECT_EQ(TileType::CURVED_RAIL, t.getTileType());
}
