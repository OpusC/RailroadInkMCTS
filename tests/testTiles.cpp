#include "Tiles.h"
#include <array>
#include <gtest/gtest.h>

using CT = ConnectionType;
using DIR = Direction;

TEST(TileTest, NoRotationCurvedRail)
{
	Tile t = Tile(TileType::CurvedRail, Rotation::Zero);
	auto expected = std::array<CT, DIR::NumDirections>{
		CT::Rail, CT::Rail, CT::None, CT::None
	};
	EXPECT_EQ(expected, t.getConnections());
}

TEST(TileTest, NinetyRotationCurvedRail)
{
	Tile t = Tile(TileType::CurvedRail, Rotation::Ninety);
	auto expected = std::array<CT, DIR::NumDirections>{
		CT::None, CT::Rail, CT::Rail, CT::None
	};
	EXPECT_EQ(expected, t.getConnections());
}

TEST(TileTest, OneEightyRotationCurvedRail)
{
	Tile t = Tile(TileType::CurvedRail, Rotation::OneEighty);

	auto expected = std::array<CT, DIR::NumDirections>{
		CT::None, CT::None, CT::Rail, CT::Rail
	};
	EXPECT_EQ(expected, t.getConnections());
}

TEST(TileTest, TwoSeventyRotation)
{
	Tile t = Tile(TileType::CurvedRail, Rotation::TwoSeventy);
	auto expected = std::array<CT, DIR::NumDirections>{
		CT::Rail, CT::None, CT::None, CT::Rail
	};
	EXPECT_EQ(expected, t.getConnections());
}

TEST(TileTest, NoRotationStraightRail)
{
	Tile t = Tile(TileType::StraightRail, Rotation::Zero);
	auto expected = std::array<CT, DIR::NumDirections>{
		CT::Rail, CT::None, CT::Rail, CT::None
	};
	EXPECT_EQ(expected, t.getConnections());
}

TEST(TileTest, NinetyRotationStraightRail)
{
	Tile t = Tile(TileType::StraightRail, Rotation::Ninety);
	auto expected = std::array<CT, DIR::NumDirections>{
		CT::None, CT::Rail, CT::None, CT::Rail
	};
	EXPECT_EQ(expected, t.getConnections());
}

TEST(TileTest, OneEightyRotationStraightRail)
{
	Tile t = Tile(TileType::StraightRail, Rotation::Ninety);
	auto expected = std::array<CT, DIR::NumDirections>{
		CT::Rail, CT::None, CT::Rail, CT::None
	};
	EXPECT_EQ(expected, t.getConnections());
}


TEST(TileTest, NoRotationSpecial6)
{
	Tile t = Tile(TileType::Special6, Rotation::Zero);
	auto expected = std::array<CT, DIR::NumDirections>{
		CT::Road, CT::Rail, CT::Road, CT::Rail
	};
	EXPECT_EQ(expected, t.getConnections());
	EXPECT_EQ(true, t.isStation);
}

TEST(TileTest, NinetyRotationSpecial6)
{
	Tile t = Tile(TileType::Special6, Rotation::Ninety);
	auto expected = std::array<CT, DIR::NumDirections>{
		CT::Rail, CT::Road, CT::Rail, CT::Road
	};
	EXPECT_EQ(expected, t.getConnections());
	EXPECT_EQ(true, t.isStation);
}

TEST(TileTest, OneEightyRotationSpecial6)
{
	Tile t = Tile(TileType::Special6, Rotation::OneEighty);
	auto expected = std::array<CT, DIR::NumDirections>{
		CT::Road, CT::Rail, CT::Road, CT::Rail
	};
	EXPECT_EQ(expected, t.getConnections());
	EXPECT_EQ(true, t.isStation);
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
