#include "Debug.h"
#include "Tiles.h"
#include <array>
#include <cassert>

void Tile::rotate()
{
	std::array<ConnectionType, NumDirections> connectionsCopy =
	  this->connections;

	this->connections[0] = connectionsCopy[3];
	this->connections[1] = connectionsCopy[0];
	this->connections[2] = connectionsCopy[1];
	this->connections[3] = connectionsCopy[2];
}

bool Tile::connects(const Tile &t1,
  const Tile &t2,
  Direction connectionDirection)
{
	LOG_DEBUG << "checking connection for direction" << connectionDirection
	          << "\n";
	assert(connectionDirection >= 0
	       and connectionDirection < Direction::NumDirections);

	auto c1 = t1.getConnections()[connectionDirection];
	auto c2 =
	  t2.getConnections()[(connectionDirection + 2) % Direction::NumDirections];

	LOG_DEBUG << "c1: " << c1 << " c2: " << c2 << "\n";
	return (c1 == c2) && (c1 != ConnectionType::None);
}

Tile::Tile(TileType tileType)
{
	assert(tileType >= 0 && tileType < NumTiles);

	struct TileData
	{
		std::array<ConnectionType, 4> connections;
		bool isStation;
	};

	using CT = ConnectionType;
	static constexpr std::array<TileData, NumTiles> tileData = { {
	  { { CT::None, CT::None, CT::None, CT::None }, false },
	  { { CT::Rail, CT::None, CT::Rail, CT::None }, false },
	  { { CT::Rail, CT::Rail, CT::None, CT::None }, false },
	  { { CT::Rail, CT::Rail, CT::None, CT::Rail }, false },
	  { { CT::Road, CT::None, CT::Road, CT::None }, false },
	  { { CT::Road, CT::Road, CT::None, CT::None }, false },
	  { { CT::Road, CT::Road, CT::None, CT::Road }, false },
	  { { CT::Road, CT::None, CT::Rail, CT::None }, true },
	  { { CT::Road, CT::Rail, CT::None, CT::None }, true },
	  { { CT::Road, CT::Rail, CT::Road, CT::Rail }, false },
	  { { CT::Road, CT::Road, CT::Rail, CT::Road }, true },
	  { { CT::Road, CT::Rail, CT::Rail, CT::Rail }, true },
	  { { CT::Road, CT::Road, CT::Road, CT::Road }, false },
	  { { CT::Rail, CT::Rail, CT::Rail, CT::Rail }, false },
	  { { CT::Road, CT::Rail, CT::Rail, CT::Road }, true },
	  { { CT::Road, CT::Rail, CT::Road, CT::Rail }, true },
	  { { CT::None, CT::None, CT::None, CT::None }, true },
	} };

	this->tileType = tileType;
	connections = tileData[tileType].connections;
	isStation = tileData[tileType].isStation;
}

Tile::Tile(TileType tileType, Rotation rotation) : Tile(tileType)
{
	assert(rotation >= Zero && rotation <= TwoSeventy);

	for (int i = 0; i < static_cast<int>(rotation); i++) {
		rotate();
	}
}

bool Tile::operator==(const Tile &t) const
{
	return (tileType == t.tileType) && (isStation == t.isStation)
	       && (connections == t.connections);
};
