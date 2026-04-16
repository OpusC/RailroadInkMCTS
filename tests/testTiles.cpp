#include "Tiles.h"
#include <gtest/gtest.h>

TEST(TileTest, NoRotation)
{
	Tile t = Tile(TileType::CurvedRail, Rotation::Zero);
	EXPECT_EQ(0b1100, t.getRails());
}

TEST(TileTest, NinetyRotationCurved)
{
	Tile t = Tile(TileType::CurvedRail, Rotation::Ninety);
	EXPECT_EQ(0b0110, t.getRails());
}

TEST(TileTest, NinetyRotationStraight)
{
	Tile t = Tile(TileType::StraightRail, Rotation::Ninety);
	EXPECT_EQ(0b0101, t.getRails());
}

TEST(TileTest, OneEightyRotation)
{
	Tile t = Tile(TileType::CurvedRail, Rotation::OneEighty);
	EXPECT_EQ(0b0011, t.getRails());
}

TEST(TileTest, TwoSeventyRotation)
{
	Tile t = Tile(TileType::CurvedRail, Rotation::TwoSeventy);
	EXPECT_EQ(0b1001, t.getRails());
}

TEST(TileTest, GetTileType)
{
	Tile t = Tile(TileType::CurvedRail, Rotation::TwoSeventy);
	EXPECT_EQ(TileType::CurvedRail, t.getTileType());
}

TEST(TileTest, DefaultConstructorNotConnectedToExit)
{
	Tile t = Tile();
	EXPECT_EQ(false, t.isConnectedToExit);
}

TEST(TileTest, TileTypeConstructorNotConnectedToExit)
{
	Tile t = Tile(TileType::CurvedRail);
	EXPECT_EQ(false, t.isConnectedToExit);
}


TEST(TileTest, TileTypeAndRotationConstructorNotConnectedToExit)
{
	Tile t = Tile(TileType::CurvedRail, Rotation::TwoSeventy);
	EXPECT_EQ(false, t.isConnectedToExit);
}

TEST(TileTest, AllParamConstructorSetsIsConnectedToExit)
{

	Tile t0 = Tile(TileType::CurvedRail, Rotation::TwoSeventy, false);
	EXPECT_EQ(false, t0.isConnectedToExit);

	Tile t1 = Tile(TileType::CurvedRail, Rotation::TwoSeventy, true);
	EXPECT_EQ(true, t1.isConnectedToExit);
}
