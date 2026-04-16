#include "Debug.h"
#include "Tiles.h"
#include <cassert>
#include <cstdint>

uint8_t Tile::rotate4(int rotation, uint8_t bytes)
{
	return static_cast<uint8_t>(((bytes >> rotation) | (bytes << (4 - rotation))) & 0b1111);
}

Tile::Tile()
{
	roads = 0b0000;
	rails = 0b0000;
	tileType = TileType::Empty;
	isConnectedToExit = false;
}

Tile::Tile(TileType tileType, Rotation rotation) noexcept
{
	assert(tileType >= 0 && tileType < NumTiles);

	switch (tileType) {
	case TileType::Empty:
		roads = 0b0000;
		rails = 0b0000;
		break;
	case TileType::StraightRail:
		roads = 0b0000;
		rails = 0b1010;
		break;
	case TileType::CurvedRail:
		roads = 0b0000;
		rails = 0b1100;
		break;
	case TileType::TRail:
		roads = 0b0000;
		rails = 0b1101;
		break;
	case TileType::StraightRoad:
		roads = 0b1010;
		rails = 0b0000;
		break;
	case TileType::CurvedRoad:
		roads = 0b1100;
		rails = 0b0000;
		break;
	case TileType::TRoad:
		roads = 0b1101;
		rails = 0b0000;
		break;
	case TileType::RoadToRail:
		roads = 0b1000;
		rails = 0b0010;
		break;
	case TileType::CurvedRoadToRail:
		roads = 0b1000;
		rails = 0b0100;
		break;
	case TileType::RoadRailUnderpass:
		roads = 0b1010;
		rails = 0b0101;
		break;
	case TileType::Special1:
		roads = 0b1101;
		rails = 0b0010;
		break;
	case TileType::Special2:
		roads = 0b1000;
		rails = 0b0111;
		break;
	case TileType::Special3:
		roads = 0b1111;
		rails = 0b0000;
		break;
	case TileType::Special4:
		roads = 0b0000;
		rails = 0b1111;
		break;
	case TileType::Special5:
		roads = 0b1001;
		rails = 0b0110;
		break;
	case TileType::Special6:
		roads = 0b1010;
		rails = 0b0101;
		break;
	default:
		assert(false && "Invalid TileType");
		break;
	}

	this->tileType = tileType;

	assert(rotation >= 0 && rotation <= TwoSeventy);
	switch (rotation) {
	case Zero:
	case Ninety:
	case OneEighty:
	case TwoSeventy:
		break;
	default:
		assert(false && "Invalid Rotation");
	}

	// roads = rotate4(rotation, roads);
	rails = rotate4(rotation, rails);
	roads = rotate4(rotation, roads);
	this->isConnectedToExit = false;
}

Tile::Tile(TileType tileType, Rotation rotation, bool isConnectedToExit) noexcept
{
	assert(tileType >= 0 && tileType < NumTiles);

	switch (tileType) {
	case TileType::Empty:
		roads = 0b0000;
		rails = 0b0000;
		break;
	case TileType::StraightRail:
		roads = 0b0000;
		rails = 0b1010;
		break;
	case TileType::CurvedRail:
		roads = 0b0000;
		rails = 0b1100;
		break;
	case TileType::TRail:
		roads = 0b0000;
		rails = 0b1101;
		break;
	case TileType::StraightRoad:
		roads = 0b1010;
		rails = 0b0000;
		break;
	case TileType::CurvedRoad:
		roads = 0b1100;
		rails = 0b0000;
		break;
	case TileType::TRoad:
		roads = 0b1101;
		rails = 0b0000;
		break;
	case TileType::RoadToRail:
		roads = 0b1000;
		rails = 0b0010;
		break;
	case TileType::CurvedRoadToRail:
		roads = 0b1000;
		rails = 0b0100;
		break;
	case TileType::RoadRailUnderpass:
		roads = 0b1010;
		rails = 0b0101;
		break;
	case TileType::Special1:
		roads = 0b1101;
		rails = 0b0010;
		break;
	case TileType::Special2:
		roads = 0b1000;
		rails = 0b0111;
		break;
	case TileType::Special3:
		roads = 0b1111;
		rails = 0b0000;
		break;
	case TileType::Special4:
		roads = 0b0000;
		rails = 0b1111;
		break;
	case TileType::Special5:
		roads = 0b1001;
		rails = 0b0110;
		break;
	case TileType::Special6:
		roads = 0b1010;
		rails = 0b0101;
		break;
	default:
		assert(false && "Invalid TileType");
		break;
	}

	this->tileType = tileType;

	assert(rotation >= 0 && rotation <= TwoSeventy);
	switch (rotation) {
	case Zero:
	case Ninety:
	case OneEighty:
	case TwoSeventy:
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
