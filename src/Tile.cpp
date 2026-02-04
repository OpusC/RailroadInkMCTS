#include "Tiles.h"

uint8_t Tile::rotate4(int rotation, uint8_t bytes) { return bytes; }

Tile::Tile(TileType tileType, Rotation rotation)
{
	switch (tileType) {
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
		throw std::invalid_argument("received invalid tiletype value");
	}

	if (rotation % 90 != 0) throw std::invalid_argument("received invalid roation value");

	roads = rotate4(rotation / 4, roads);
	rails = rotate4(rotation / 4, rails);
}
