#ifndef TILES_H
#define TILES_H

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

inline bool isSpecialTile(TileType t) { return t >= Special1 && t <= Special6; }

class Tile
{
  public:
	static uint8_t rotate4(int rotation, uint8_t bytes);

  private:
	TileType tileType;
	uint8_t roads;
	uint8_t rails;


  public:
	Tile();
	Tile(TileType tileType, Rotation rotation) noexcept;
	Tile(TileType tileType, Rotation rotation, bool isConnectedToExit) noexcept;

	uint8_t getRoads() const { return roads; }
	uint8_t getRails() const { return rails; }
	TileType getTileType() const { return tileType; }

	bool operator==(const Tile &t) const;

	bool isConnectedToExit;
};

#endif
