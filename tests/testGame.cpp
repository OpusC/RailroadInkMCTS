#include "Game.h"
#include "Tiles.h"
#include <gtest/gtest.h>

// TEST(GameTest, getScoreShouldReturnZeroOnEmptyBoard)
// {
// 	Game game = Game();
// 	ASSERT_EQ(0, game.getScore());
// }


TEST(GameTest, rollDiceShouldReturnNonNullTileType)
{
	Game game = Game();
	std::array<TileType, 4> diceRoll = game.rollDice();

	for (TileType t : diceRoll) {
		ASSERT_GT(t, TileType::EMPTY);
		ASSERT_LT(t, TileType::SPECIAL_1);
	}
}

// TEST(GameTest, rollDiceShouldReturnTwoRoutesOneJunctionOneOverpass)
// {
// 	Game game = Game();
// 	std::array<TileType, 4> diceRoll = game.rollDice();
//
// 	const std::set<TileType> routeDieFaces = {
// 		STRAIGHT_RAIL, CURVED_RAIL, T_RAIL, STRAIGHT_ROAD, CURVED_ROAD, T_ROAD
// 	};
//
// 	const std::set<TileType> junctionDieFaces = {
// 		T_RAIL, T_ROAD, ROAD_TO_RAIL, CURVED_ROAD_TO_RAIL
// 	};
//
// 	const std::set<TileType> overpassDieFaces = {
// 		ROAD_RAIL_UNDERPASS, T_RAIL, T_ROAD, STRAIGHT_RAIL, STRAIGHT_ROAD, CURVED_RAIL
// 	};
//
// 	// Dice 0 and 1 are the identical route dice
// 	ASSERT_TRUE(routeDieFaces.count(diceRoll[0])) << "Die 0 (route) rolled an invalid face";
// 	ASSERT_TRUE(routeDieFaces.count(diceRoll[1])) << "Die 1 (route) rolled an invalid face";
//
// 	// Die 2 is the junction die
// 	ASSERT_TRUE(junctionDieFaces.count(diceRoll[2])) << "Die 2 (junction) rolled an invalid face";
//
// 	// Die 3 is the overpass die
// 	ASSERT_TRUE(overpassDieFaces.count(diceRoll[3])) << "Die 3 (overpass) rolled an invalid face";
// }
//
// TEST(GameTest, rollDiceShouldUseAllFacesOfEachDie)
// {
// 	Game game = Game();
//
// 	const std::set<TileType> routeDieFaces = {
// 		STRAIGHT_RAIL, CURVED_RAIL, T_RAIL, STRAIGHT_ROAD, CURVED_ROAD, T_ROAD
// 	};
// 	const std::set<TileType> junctionDieFaces = {
// 		T_RAIL, T_ROAD, ROAD_TO_RAIL, CURVED_ROAD_TO_RAIL
// 	};
// 	const std::set<TileType> overpassDieFaces = {
// 		ROAD_RAIL_UNDERPASS, T_RAIL, T_ROAD, STRAIGHT_RAIL, STRAIGHT_ROAD, CURVED_RAIL
// 	};
//
// 	std::set<TileType> seenDie0, seenDie1, seenDie2, seenDie3;
//
// 	// Roll enough times that seeing every face is near-certain
// 	for (int i = 0; i < 1000; i++) {
// 		auto roll = game.rollDice();
// 		seenDie0.insert(roll[0]);
// 		seenDie1.insert(roll[1]);
// 		seenDie2.insert(roll[2]);
// 		seenDie3.insert(roll[3]);
// 	}
//
// 	ASSERT_EQ(seenDie0, routeDieFaces);
// 	ASSERT_EQ(seenDie1, routeDieFaces);
// 	ASSERT_EQ(seenDie2, junctionDieFaces);
// 	ASSERT_EQ(seenDie3, overpassDieFaces);
// }
