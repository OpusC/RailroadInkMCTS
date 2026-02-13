#ifndef TILES_H
#define TILES_H

#include <cstdint>

enum TileType {
	EMPTY = 0,
	STRAIGHT_RAIL,
	CURVED_RAIL,
	T_RAIL,
	STRAIGHT_ROAD,
	CURVED_ROAD,
	T_ROAD,
	ROAD_TO_RAIL,
	CURVED_ROAD_TO_RAIL,
	ROAD_RAIL_UNDERPASS,
	SPECIAL_1,
	SPECIAL_2,
	SPECIAL_3,
	SPECIAL_4,
	SPECIAL_5,
	SPECIAL_6,
	NUM_TILES
};

enum Rotation { NONE = 0, NINETY, ONE_EIGHTY, TWO_SEVENTY };

class Tile
{
  private:
	TileType tileType;
	uint8_t roads;
	uint8_t rails;

	static uint8_t rotate4(int rotation, uint8_t bytes);

  public:
	Tile();
	Tile(TileType tileType, Rotation rotation) noexcept;
	uint8_t getRoads() const { return roads; }
	uint8_t getRails() const { return rails; }
	bool operator==(const Tile &t) const;
	TileType getTileType() const { return tileType; }
};

#endif
