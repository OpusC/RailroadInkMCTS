#include "Debug.h"
#include "Tiles.h"
#include <cassert>

// TODO: STUB
void Tile::rotate() {}

Tile::Tile()
{
	connections = { ConnectionType::NONE,
		ConnectionType::NONE,
		ConnectionType::NONE,
		ConnectionType::NONE };
	tileType = TileType::EMPTY;
	isConnectedToExit = false;
}

Tile::Tile(TileType tileType)
{
	assert(tileType >= 0 && tileType < NUM_TILES);

	struct TileData
	{
		std::array<ConnectionType, 4> connections;
		bool isStation;
	};

	static constexpr std::array<TileData, NUM_TILES> tileData = { {
	  { { NONE, NONE, NONE, NONE }, false },// EMPTY
	  { { RAIL, NONE, RAIL, NONE }, false },// STRAIGHT_RAIL
	  { { RAIL, RAIL, NONE, NONE }, false },// CURVED_RAIL
	  { { RAIL, RAIL, NONE, RAIL }, false },// T_RAIL
	  { { ROAD, NONE, ROAD, NONE }, false },// STRAIGHT_ROAD
	  { { ROAD, ROAD, NONE, NONE }, false },// CURVED_ROAD
	  { { ROAD, ROAD, NONE, ROAD }, false },// T_ROAD
	  { { ROAD, NONE, RAIL, NONE }, true },// ROAD_TO_RAIL
	  { { ROAD, RAIL, NONE, NONE }, true },// CURVED_ROAD_TO_RAIL
	  { { ROAD, RAIL, ROAD, RAIL }, false },// ROAD_RAIL_UNDERPASS
	  { { ROAD, ROAD, RAIL, ROAD }, true },// SPECIAL_1
	  { { ROAD, RAIL, RAIL, RAIL }, true },// SPECIAL_2
	  { { ROAD, ROAD, ROAD, ROAD }, false },// SPECIAL_3
	  { { RAIL, RAIL, RAIL, RAIL }, false },// SPECIAL_4
	  { { ROAD, RAIL, RAIL, ROAD }, true },// SPECIAL_5
	  { { ROAD, RAIL, ROAD, RAIL }, true },// SPECIAL_6
	} };

	this->tileType = tileType;
	connections = tileData[tileType].connections;
	isStation = tileData[tileType].isStation;
	isConnectedToExit = false;
}

Tile::Tile(TileType tileType, Rotation rotation)
{
	assert(tileType >= 0 && tileType < NUM_TILES);

	switch (tileType) {
	case TileType::EMPTY:
		roads = 0b0000;
		rails = 0b0000;
		break;
	case TileType::STRAIGHT_RAIL:
		roads = 0b0000;
		rails = 0b1010;
		break;
	case TileType::CURVED_RAIL:
		roads = 0b0000;
		rails = 0b1100;
		break;
	case TileType::T_RAIL:
		roads = 0b0000;
		rails = 0b1101;
		break;
	case TileType::STRAIGHT_ROAD:
		roads = 0b1010;
		rails = 0b0000;
		break;
	case TileType::CURVED_ROAD:
		roads = 0b1100;
		rails = 0b0000;
		break;
	case TileType::T_ROAD:
		roads = 0b1101;
		rails = 0b0000;
		break;
	case TileType::ROAD_TO_RAIL:
		roads = 0b1000;
		rails = 0b0010;
		break;
	case TileType::CURVED_ROAD_TO_RAIL:
		roads = 0b1000;
		rails = 0b0100;
		break;
	case TileType::ROAD_RAIL_UNDERPASS:
		roads = 0b1010;
		rails = 0b0101;
		break;
	case TileType::SPECIAL_1:
		roads = 0b1101;
		rails = 0b0010;
		break;
	case TileType::SPECIAL_2:
		roads = 0b1000;
		rails = 0b0111;
		break;
	case TileType::SPECIAL_3:
		roads = 0b1111;
		rails = 0b0000;
		break;
	case TileType::SPECIAL_4:
		roads = 0b0000;
		rails = 0b1111;
		break;
	case TileType::SPECIAL_5:
		roads = 0b1001;
		rails = 0b0110;
		break;
	case TileType::SPECIAL_6:
		roads = 0b1010;
		rails = 0b0101;
		break;
	default:
		assert(false && "Invalid TileType");
		break;
	}

	this->tileType = tileType;

	assert(rotation >= 0 && rotation <= TWO_SEVENTY);
	switch (rotation) {
	case ZERO:
	case NINETY:
	case ONE_EIGHTY:
	case TWO_SEVENTY:
		break;
	default:
		assert(false && "Invalid Rotation");
	}

	// roads = rotate4(rotation, roads);
	rails = rotate4(rotation, rails);
	roads = rotate4(rotation, roads);
	this->isConnectedToExit = false;
}

Tile::Tile(TileType tileType,
  Rotation rotation,
  bool isConnectedToExit) noexcept
{
	assert(tileType >= 0 && tileType < NUM_TILES);

	switch (tileType) {
	case TileType::EMPTY:
		roads = 0b0000;
		rails = 0b0000;
		break;
	case TileType::STRAIGHT_RAIL:
		roads = 0b0000;
		rails = 0b1010;
		break;
	case TileType::CURVED_RAIL:
		roads = 0b0000;
		rails = 0b1100;
		break;
	case TileType::T_RAIL:
		roads = 0b0000;
		rails = 0b1101;
		break;
	case TileType::STRAIGHT_ROAD:
		roads = 0b1010;
		rails = 0b0000;
		break;
	case TileType::CURVED_ROAD:
		roads = 0b1100;
		rails = 0b0000;
		break;
	case TileType::T_ROAD:
		roads = 0b1101;
		rails = 0b0000;
		break;
	case TileType::ROAD_TO_RAIL:
		roads = 0b1000;
		rails = 0b0010;
		break;
	case TileType::CURVED_ROAD_TO_RAIL:
		roads = 0b1000;
		rails = 0b0100;
		break;
	case TileType::ROAD_RAIL_UNDERPASS:
		roads = 0b1010;
		rails = 0b0101;
		break;
	case TileType::SPECIAL_1:
		roads = 0b1101;
		rails = 0b0010;
		break;
	case TileType::SPECIAL_2:
		roads = 0b1000;
		rails = 0b0111;
		break;
	case TileType::SPECIAL_3:
		roads = 0b1111;
		rails = 0b0000;
		break;
	case TileType::SPECIAL_4:
		roads = 0b0000;
		rails = 0b1111;
		break;
	case TileType::SPECIAL_5:
		roads = 0b1001;
		rails = 0b0110;
		break;
	case TileType::SPECIAL_6:
		roads = 0b1010;
		rails = 0b0101;
		break;
	default:
		assert(false && "Invalid TileType");
		break;
	}

	this->tileType = tileType;

	assert(rotation >= 0 && rotation <= TWO_SEVENTY);
	switch (rotation) {
	case ZERO:
	case NINETY:
	case ONE_EIGHTY:
	case TWO_SEVENTY:
		break;
	default:
		assert(false && "Invalid Rotation");
	}

	// roads = rotate4(rotation, roads);
	rails = rotate4(rotation, rails);
	roads = rotate4(rotation, roads);
	this->isConnectedToExit = isConnectedToExit;
}

bool Tile::operator==(const Tile &t) const
{
	bool a = roads == t.roads;
	if (a) { LOG_DEBUG << "roads are equal\n"; }
	bool b = rails == t.rails;
	if (b) { LOG_DEBUG << "rails are equal\n"; }
	bool c = tileType == t.tileType;
	if (c) { LOG_DEBUG << "tiletype is equal\n"; }
	return (roads == t.roads && rails == t.rails && tileType == t.tileType);
};
