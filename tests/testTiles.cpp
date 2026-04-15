#include "Tiles.h"
#include <gtest/gtest.h>

TEST(TileTest, NoRotation)
{
	Tile t = Tile(TileType::CURVED_RAIL, Rotation::ZERO);
	EXPECT_EQ(0b1100, t.getRails());
}

TEST(TileTest, NinetyRotationCurved)
{
	Tile t = Tile(TileType::CURVED_RAIL, Rotation::NINETY);
	EXPECT_EQ(0b0110, t.getRails());
}

TEST(TileTest, NinetyRotationStraight)
{
	Tile t = Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY);
	EXPECT_EQ(0b0101, t.getRails());
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

TEST(TileTest, DefaultConstructorNotConnectedToExit)
{
	Tile t = Tile();
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

// rotate4 bug: the expression
//   (bytes >> rotation) | (bytes << (4 - rotation) & 0b1111)
// is parsed as:
//   (bytes >> rotation) | ((bytes << (4 - rotation)) & 0b1111)
// because & binds tighter than |. The mask covers only the left-shift term.
// When bytes has upper bits set, (bytes >> rotation) can produce a value
// above 0b1111, which leaks into the result unchecked.
//
// The fix is: ((bytes >> rotation) | (bytes << (4 - rotation))) & 0b1111
//
// The test cases below use bytes values with only upper bits set (lower
// nibble = 0b0000). Rotating zero lower bits must produce zero — the
// expected value is unambiguous. The buggy version returns non-zero because
// the right-shifted upper bits leak through without the outer mask.

TEST(Rotate4Test, OutputIsAlwaysWithinLower4Bits)
{
	// Upper bits in input must not appear in output.
	// Buggy: (0b00100000 >> 1) = 0b00010000 (16) leaks through unmasked.
	EXPECT_LE(Tile::rotate4(1, 0b00100000), 0x0F);
	// Buggy: (0b01000000 >> 1) = 0b00100000 (32) leaks through unmasked.
	EXPECT_LE(Tile::rotate4(1, 0b01000000), 0x0F);
	// Buggy: (0b11000000 >> 2) = 0b00110000 (48) leaks through unmasked.
	EXPECT_LE(Tile::rotate4(2, 0b11000000), 0x0F);
}

TEST(Rotate4Test, RotatingZeroLowerBitsGivesZero)
{
	// Lower nibble is 0b0000 in all cases, so all rotations must return 0.
	// Buggy version returns non-zero because unmasked right-shift of upper
	// bits pollutes the result.
	EXPECT_EQ(0b0000, Tile::rotate4(1, 0b00100000)); // buggy returns 16
	EXPECT_EQ(0b0000, Tile::rotate4(1, 0b01000000)); // buggy returns 32
	EXPECT_EQ(0b0000, Tile::rotate4(2, 0b11000000)); // buggy returns 48
}

TEST(Rotate4Test, FourNinetyDegreeRotationsIsIdentity)
{
	// Rotating any 4-bit value by 90° four times must return the original.
	// This catches any rotation that produces values outside [0, 15], since
	// composing such results would drift further from the original.
	for (uint8_t v = 0; v <= 0b1111; v++) {
		uint8_t result = v;
		for (int i = 0; i < 4; i++)
			result = Tile::rotate4(1, result);
		EXPECT_EQ(v, result) << "Identity failed for v=" << (int)v;
	}
}
