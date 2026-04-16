#ifndef TILES_H
#define TILES_H

#include <array>

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

enum Rotation { ZERO = 0, NINETY, ONE_EIGHTY, TWO_SEVENTY };

enum ConnectionType { NONE = 0, ROAD, RAIL };

enum Direction { UP = 0, RIGHT, DOWN, LEFT };

inline bool isSpecialTile(TileType t)
{
	return t >= SPECIAL_1 && t <= SPECIAL_6;
}

class Tile
{
  private:
	TileType tileType;
	std::array<ConnectionType, 4> connections;

  public:
	Tile();
	Tile(TileType tileType);
	Tile(TileType tileType, Rotation rotation);
	Tile(TileType tileType, Rotation rotation, bool isConnectedToExit);

	void rotate();
	bool connects(Direction direction, ConnectionType connectionType) const;
	TileType getTileType() const { return tileType; }

	bool operator==(const Tile &t) const;

	bool isConnectedToExit;
	bool isStation;
};

#endif
