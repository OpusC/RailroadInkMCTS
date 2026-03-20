#include "Game.h"
#include "Tiles.h"
#include <gtest/gtest.h>
#include <set>

TEST(GameTest, rollDiceShouldReturnNonNullTileType)
{
	Game game = Game();
	std::array<TileType, 4> diceRoll = game.rollDice();

	for (TileType t : diceRoll) {
		ASSERT_GT(t, TileType::EMPTY);
		ASSERT_LT(t, TileType::SPECIAL_1);
	}
}

TEST(GameTest, rollDiceShouldReturnTwoRoutesOneJunctionOneOverpass)
{
	// Use a fixed seed so the test is deterministic.
	Game game = Game(42);

	const std::set<TileType> routeDieFaces = {
		STRAIGHT_RAIL, CURVED_RAIL, T_RAIL, STRAIGHT_ROAD, CURVED_ROAD, T_ROAD
	};
	const std::set<TileType> junctionDieFaces = {
		T_RAIL, T_ROAD, ROAD_TO_RAIL, CURVED_ROAD_TO_RAIL
	};
	const std::set<TileType> overpassDieFaces = {
		ROAD_RAIL_UNDERPASS, T_RAIL, T_ROAD, STRAIGHT_RAIL, STRAIGHT_ROAD, CURVED_RAIL
	};

	// Run many rolls to check every result stays within the valid face sets.
	for (int i = 0; i < 500; i++) {
		auto roll = game.rollDice();
		ASSERT_TRUE(routeDieFaces.count(roll[0]))   << "Die 0 (route) rolled an invalid face";
		ASSERT_TRUE(routeDieFaces.count(roll[1]))   << "Die 1 (route) rolled an invalid face";
		ASSERT_TRUE(junctionDieFaces.count(roll[2])) << "Die 2 (junction) rolled an invalid face";
		ASSERT_TRUE(overpassDieFaces.count(roll[3])) << "Die 3 (overpass) rolled an invalid face";
	}
}

TEST(GameTest, rollDiceShouldUseAllFacesOfEachDie)
{
	Game game = Game(0);

	const std::set<TileType> routeDieFaces = {
		STRAIGHT_RAIL, CURVED_RAIL, T_RAIL, STRAIGHT_ROAD, CURVED_ROAD, T_ROAD
	};
	const std::set<TileType> junctionDieFaces = {
		T_RAIL, T_ROAD, ROAD_TO_RAIL, CURVED_ROAD_TO_RAIL
	};
	const std::set<TileType> overpassDieFaces = {
		ROAD_RAIL_UNDERPASS, T_RAIL, T_ROAD, STRAIGHT_RAIL, STRAIGHT_ROAD, CURVED_RAIL
	};

	std::set<TileType> seenDie0, seenDie1, seenDie2, seenDie3;

	// Roll enough times that seeing every face is near-certain.
	// Probability of missing any single face after 1000 rolls: (5/6)^1000 ≈ 0.
	for (int i = 0; i < 1000; i++) {
		auto roll = game.rollDice();
		seenDie0.insert(roll[0]);
		seenDie1.insert(roll[1]);
		seenDie2.insert(roll[2]);
		seenDie3.insert(roll[3]);
	}

	EXPECT_EQ(seenDie0, routeDieFaces);
	EXPECT_EQ(seenDie1, routeDieFaces);
	EXPECT_EQ(seenDie2, junctionDieFaces);
	EXPECT_EQ(seenDie3, overpassDieFaces);
}
