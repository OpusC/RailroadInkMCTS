#include "Tiles.h"
#include <gtest/gtest.h>

TEST(TileTest, NoRotation)
{
	Tile t = Tile(TileType::CURVED_RAIL, Rotation::ZERO);
	EXPECT_TRUE(t.connects(Direction::UP, ConnectionType::RAIL));
	EXPECT_TRUE(t.connects(Direction::RIGHT, ConnectionType::RAIL));
	EXPECT_FALSE(t.connects(Direction::DOWN, ConnectionType::RAIL));
	EXPECT_FALSE(t.connects(Direction::LEFT, ConnectionType::RAIL));
}

TEST(TileTest, NinetyRotationCurved)
{
	Tile t = Tile(TileType::CURVED_RAIL, Rotation::NINETY);
	EXPECT_FALSE(t.connects(Direction::UP, ConnectionType::RAIL));
	EXPECT_TRUE(t.connects(Direction::RIGHT, ConnectionType::RAIL));
	EXPECT_TRUE(t.connects(Direction::DOWN, ConnectionType::RAIL));
	EXPECT_FALSE(t.connects(Direction::LEFT, ConnectionType::RAIL));
}

TEST(TileTest, NinetyRotationStraight)
{
	Tile t = Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY);
	EXPECT_FALSE(t.connects(Direction::UP, ConnectionType::RAIL));
	EXPECT_TRUE(t.connects(Direction::RIGHT, ConnectionType::RAIL));
	EXPECT_FALSE(t.connects(Direction::DOWN, ConnectionType::RAIL));
	EXPECT_TRUE(t.connects(Direction::LEFT, ConnectionType::RAIL));
}

TEST(TileTest, OneEightyRotation)
{
	Tile t = Tile(TileType::CURVED_RAIL, Rotation::ONE_EIGHTY);
	EXPECT_FALSE(t.connects(Direction::UP, ConnectionType::RAIL));
	EXPECT_FALSE(t.connects(Direction::RIGHT, ConnectionType::RAIL));
	EXPECT_TRUE(t.connects(Direction::DOWN, ConnectionType::RAIL));
	EXPECT_TRUE(t.connects(Direction::LEFT, ConnectionType::RAIL));
}

TEST(TileTest, TwoSeventyRotation)
{
	Tile t = Tile(TileType::CURVED_RAIL, Rotation::TWO_SEVENTY);
	EXPECT_TRUE(t.connects(Direction::UP, ConnectionType::RAIL));
	EXPECT_FALSE(t.connects(Direction::RIGHT, ConnectionType::RAIL));
	EXPECT_FALSE(t.connects(Direction::DOWN, ConnectionType::RAIL));
	EXPECT_TRUE(t.connects(Direction::LEFT, ConnectionType::RAIL));
}

TEST(TileTest, GetTileType)
{
	Tile t = Tile(TileType::CURVED_RAIL, Rotation::TWO_SEVENTY);
	EXPECT_EQ(TileType::CURVED_RAIL, t.getTileType());
}

TEST(TileTest, DefaultConstructorNotConnectedToExit)
{
	Tile t = Tile();
	EXPECT_EQ(false, t.isConnectedToExit);
}

TEST(TileTest, TileTypeConstructorNotConnectedToExit)
{
	Tile t = Tile(TileType::CURVED_RAIL);
	EXPECT_EQ(false, t.isConnectedToExit);
}


TEST(TileTest, TileTypeAndRotationConstructorNotConnectedToExit)
{
	Tile t = Tile(TileType::CURVED_RAIL, Rotation::TWO_SEVENTY);
	EXPECT_EQ(false, t.isConnectedToExit);
}

TEST(TileTest, AllParamConstructorSetsIsConnectedToExit)
{

	Tile t0 = Tile(TileType::CURVED_RAIL, Rotation::TWO_SEVENTY, false);
	EXPECT_EQ(false, t0.isConnectedToExit);

	Tile t1 = Tile(TileType::CURVED_RAIL, Rotation::TWO_SEVENTY, true);
	EXPECT_EQ(true, t1.isConnectedToExit);
}
