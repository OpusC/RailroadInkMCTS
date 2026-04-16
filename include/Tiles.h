#ifndef TILES_H
#define TILES_H

#include <array>
#include <cstdint>

enum TileType {
	Empty = 0,
	StraightRail,
	CurvedRail,
	TRail,
	StraightRoad,
	CurvedRoad,
	TRoad,
	RoadToRail,
	CurvedRoadToRail,
	RoadRailUnderpass,
	Special1,
	Special2,
	Special3,
	Special4,
	Special5,
	Special6,
	NumTiles
};

enum Rotation { Zero = 0, Ninety, OneEighty, TwoSeventy };

enum ConnectionType { None = 0, Road, Rail };

enum Direction { Up = 0, Right, Down, Left };

inline bool isSpecialTile(TileType t) { return t >= Special1 && t <= Special6; }

class Tile
{
  private:
	TileType tileType;
	std::array<ConnectionType, 4> connections;
	uint8_t roads;
	uint8_t rails;

  public:
	Tile();
	Tile(TileType tileType);
	Tile(TileType tileType, Rotation rotation);
	Tile(TileType tileType, Rotation rotation, bool isConnectedToExit);

	void rotate();
	bool connects(Direction direction, ConnectionType connectionType) const;
	TileType getTileType() const { return tileType; }
	uint8_t getRoads() const { return roads; }
	uint8_t getRails() const { return rails; }

	bool operator==(const Tile &t) const;

	bool isConnectedToExit;
	bool isStation;
};

#endif
