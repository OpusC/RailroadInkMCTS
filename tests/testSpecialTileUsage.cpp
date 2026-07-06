#include "SpecialTileUsage.h"
#include <gtest/gtest.h>

TEST(SpecialTileUsageTest, DefaultAllUnused)
{
	SpecialTileUsage s;
	EXPECT_FALSE(s.isUsed(TileType::Special1));
	EXPECT_FALSE(s.isUsed(TileType::Special6));
	EXPECT_FALSE(s.allUsed());
}

TEST(SpecialTileUsageTest, MarkUsed)
{
	SpecialTileUsage s;
	s.markUsed(TileType::Special1);
	EXPECT_TRUE(s.isUsed(TileType::Special1));
	EXPECT_FALSE(s.isUsed(TileType::Special2));
}

TEST(SpecialTileUsageTest, AllUsed)
{
	SpecialTileUsage s;
	for (auto tile : { TileType::Special1,
	       TileType::Special2,
	       TileType::Special3,
	       TileType::Special4,
	       TileType::Special5,
	       TileType::Special6 })
		s.markUsed(tile);
	EXPECT_TRUE(s.allUsed());
}

TEST(SpecialTileUsageTest, NonSpecialTileIgnored)
{
	SpecialTileUsage s;
	s.markUsed(TileType::StraightRail);
	EXPECT_FALSE(s.isUsed(TileType::StraightRail));
	EXPECT_FALSE(s.allUsed());
}

TEST(SpecialTileUsageTest, MarkUsedNoFallthrough)
{
	for (auto tile : { TileType::Special1,
	       TileType::Special2,
	       TileType::Special3,
	       TileType::Special4,
	       TileType::Special5,
	       TileType::Special6 }) {
		SpecialTileUsage s;
		s.markUsed(tile);
		EXPECT_TRUE(s.isUsed(tile));
		// all others must remain false
		for (auto other : { TileType::Special1,
		       TileType::Special2,
		       TileType::Special3,
		       TileType::Special4,
		       TileType::Special5,
		       TileType::Special6 }) {
			if (other != tile) { EXPECT_FALSE(s.isUsed(other)); }
		}
	}
}
