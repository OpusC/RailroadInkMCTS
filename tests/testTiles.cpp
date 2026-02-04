#include "Tiles.h"
#include <gtest/gtest.h>

TEST(TileTest, NoRotation)
{
	Tile t = Tile(TileType::STRAIGHT_RAIL, Rotation::NONE);
	EXPECT_EQ(0b1010, t.getRails());
}

TEST(TileTest, NinetyRotation)
{
	Tile t = Tile(TileType::STRAIGHT_RAIL, Rotation::NONE);
	EXPECT_EQ(0b0100, t.getRails());
}

TEST(TileTest, OneEightyRotation)
{
	Tile t = Tile(TileType::STRAIGHT_RAIL, Rotation::NONE);
	EXPECT_EQ(0b0010, t.getRails());
}

TEST(TileTest, TwoSeventyRotation)
{
	Tile t = Tile(TileType::STRAIGHT_RAIL, Rotation::NONE);
	EXPECT_EQ(0b0001, t.getRails());
}
