#include "Debug.h"
#include "Tiles.h"
#include <array>
#include <cassert>

// TODO: STUB
void Tile::rotate() {}

bool Tile::connects(const Tile &t1,
  const Tile &t2,
  Direction connectionDirection)
{
	LOG_DEBUG << "in tileConnect\n";
	assert(connectionDirection >= 0
	       and connectionDirection < Direction::NumDirections);

	LOG_DEBUG << "in tileConnect\n";

	auto c1 = t1.getConnections()[connectionDirection];
	auto c2 =
	  t2.getConnections()[(connectionDirection + 2) % Direction::NumDirections];

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
	} };

	this->tileType = tileType;
	connections = tileData[tileType].connections;
	isStation = tileData[tileType].isStation;
	isConnectedToExit = false;
}

Tile::Tile(TileType tileType, Rotation rotation) : Tile(tileType)
{
	assert(rotation >= Zero && rotation <= TwoSeventy);

	for (int i = 0; i <= static_cast<int>(rotation); i++) {
		rotate();
	}
}

Tile::Tile(TileType tileType, Rotation rotation, bool isConnectedToExit)
  : Tile(tileType, rotation)
{
	this->isConnectedToExit = isConnectedToExit;
}

bool Tile::operator==(const Tile &t) const
{
	return (tileType == t.tileType) && (isStation == t.isStation)
	       && (connections == t.connections);
};
