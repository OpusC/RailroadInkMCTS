#pragma once

#include "TileEnums.h"
#include <array>

class Tile
{
  private:
	TileType tileType{ Empty };
	std::array<ConnectionType, NumDirections> connections{ None,
		None,
		None,
		None };
	bool isStation{ false };

  public:
	Tile() = default;
	Tile(TileType tileType);
	Tile(TileType tileType, Rotation rotation);

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
	bool getIsStation() const { return isStation; }
};
