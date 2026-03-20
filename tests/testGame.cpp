#include "Game.h"
#include "Tiles.h"
#include <array>
#include <gtest/gtest.h>
#include <set>

// 4 moves each directly adjacent to a board exit, plus SPECIAL_4 (all rails)
// chained behind the rail exit at (3,0).
static std::array<Move, 5> turn1WithSpecial4()
{
	return {
		Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 0 },    // rail exit (3,-1)
		Move{ Tile(TileType::STRAIGHT_ROAD, Rotation::NONE), 1, 0 },    // road exit (1,-1)
		Move{ Tile(TileType::STRAIGHT_ROAD, Rotation::NONE), 5, 0 },    // road exit (5,-1)
		Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 0, 1 },  // rail exit (-1,1)
		Move{ Tile(TileType::SPECIAL_4, Rotation::NONE), 3, 1 },        // all-rail, chains to (3,0)
	};
}

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

TEST(GameTest, ValidateMoveShouldAcceptValidSpecialTile)
{
	Game game;
	EXPECT_TRUE(game.validateMove(turn1WithSpecial4()));
}

TEST(GameTest, PlayMoveMarksSpecialTileAsUsed)
{
	Game game;
	game.playMove(turn1WithSpecial4());
	EXPECT_EQ(1, game.getSpecialTilesUsed());
}

TEST(GameTest, DoubleUseOfSameSpecialTileIsRejected)
{
	Game game;
	game.playMove(turn1WithSpecial4());

	std::array<Move, 5> turn2 = {
		Move{ Tile(TileType::STRAIGHT_ROAD, Rotation::NINETY), 0, 3 },  // road exit (-1,3)
		Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 0, 5 },  // rail exit (-1,5)
		Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 6, 1 },  // rail exit (7,1)
		Move{ Tile(TileType::STRAIGHT_ROAD, Rotation::NINETY), 6, 3 },  // road exit (7,3)
		Move{ Tile(TileType::SPECIAL_4, Rotation::NONE), 3, 2 },        // SPECIAL_4 already used
	};

	EXPECT_FALSE(game.validateMove(turn2));
}

TEST(GameTest, SpecialTileInRegularSlotIsRejected)
{
	Game game;
	std::array<Move, 5> moves = {
		Move{ Tile(TileType::SPECIAL_1, Rotation::NONE), 3, 0 },   // special in slot 0
		Move{ Tile(TileType::STRAIGHT_ROAD, Rotation::NONE), 1, 0 },
		Move{ Tile(TileType::STRAIGHT_ROAD, Rotation::NONE), 5, 0 },
		Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 0, 1 },
		Move{},
	};

	EXPECT_FALSE(game.validateMove(moves));
}

TEST(GameTest, TotalSpecialTileCapIsEnforcedAfterThreeUses)
{
	Game game;

	// Turn 1: SPECIAL_4 (all rails) at (3,1), chains to rail exit via (3,0)
	game.playMove(turn1WithSpecial4());

	// Turn 2: SPECIAL_3 (all roads) at (1,1), chains to road exit via (1,0)
	game.playMove({
		Move{ Tile(TileType::STRAIGHT_ROAD, Rotation::NINETY), 0, 3 },
		Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 0, 5 },
		Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 6, 1 },
		Move{ Tile(TileType::STRAIGHT_ROAD, Rotation::NINETY), 6, 3 },
		Move{ Tile(TileType::SPECIAL_3, Rotation::NONE), 1, 1 },
	});

	// Turn 3: SPECIAL_1 at (5,1), roads connect up to STRAIGHT_ROAD at (5,0) to exit
	game.playMove({
		Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NINETY), 6, 5 },
		Move{ Tile(TileType::STRAIGHT_ROAD, Rotation::NONE), 1, 6 },
		Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 6 },
		Move{ Tile(TileType::STRAIGHT_ROAD, Rotation::NONE), 5, 6 },
		Move{ Tile(TileType::SPECIAL_1, Rotation::NONE), 5, 1 },
	});

	EXPECT_EQ(3, game.getSpecialTilesUsed());

	// Turn 4: these 4 regular moves are valid (connect via already-placed tiles)
	std::array<Move, 5> turn4 = {
		Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 2 },    // via SPECIAL_4 at (3,1)
		Move{ Tile(TileType::STRAIGHT_RAIL, Rotation::NONE), 3, 3 },    // via (3,2) chain
		Move{ Tile(TileType::STRAIGHT_ROAD, Rotation::NONE), 1, 2 },    // via SPECIAL_3 at (1,1)
		Move{ Tile(TileType::STRAIGHT_ROAD, Rotation::NINETY), 4, 1 },  // via SPECIAL_1 at (5,1)
		Move{},
	};
	EXPECT_TRUE(game.validateMove(turn4));

	// Adding any special tile must be rejected — cap already reached
	turn4[4] = Move{ Tile(TileType::SPECIAL_5, Rotation::NONE), 1, 3 };
	EXPECT_FALSE(game.validateMove(turn4));
}
