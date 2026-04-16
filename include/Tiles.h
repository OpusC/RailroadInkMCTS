#ifndef TILES_H
#define TILES_H

#include <array>

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
	Border,
	NumTiles,
};

enum Rotation { Zero = 0, Ninety, OneEighty, TwoSeventy };

enum ConnectionType { None = 0, Road, Rail };

enum Direction { Up = 0, Right, Down, Left, NumDirections };

inline bool isSpecialTile(TileType t) { return t >= Special1 && t <= Special6; }

class Tile
{
  private:
	TileType tileType{ Empty };
	std::array<ConnectionType, NumDirections> connections{ None,
		None,
		None,
		None };

  public:
	Tile() = default;
	Tile(TileType tileType);
	Tile(TileType tileType, Rotation rotation);
	Tile(TileType tileType, Rotation rotation, bool isConnectedToExit);

	/*
	 * Checks if the tile, when placed beside eachother, will connect.
	 * ConnectionDirection is relative to t1
	 */
	static bool
	  connects(const Tile &t1, const Tile &t2, Direction connectionDirection);

	void rotate();
	TileType getTileType() const { return tileType; }
	const std::array<ConnectionType, NumDirections> &getConnections() const
	{
		return connections;
	}

	bool operator==(const Tile &t) const;

	bool isConnectedToExit{ false };
	bool isStation{ false };
};

#endif
