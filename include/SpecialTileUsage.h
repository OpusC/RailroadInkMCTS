#pragma once

#include "TileEnums.h"
#include <cassert>
#include <stdexcept>
class SpecialTileUsage
{
  public:
	bool isUsed(
	  TileType tile) const;// TODO: have isSpecialTile in TileType enum/class
	void markUsed(TileType tile);
	bool allUsed() const;
	bool operator[](int index) const
	{
		assert(index >= 0);
		assert(index <= 5);
		switch (index) {
		case 0:
			return tileA;
		case 1:
			return tileB;
		case 2:
			return tileC;
		case 3:
			return tileD;
		case 4:
			return tileE;
		case 5:
			return tileF;
		default:
			throw std::invalid_argument("Invalid index");
		}
	}

  private:
	bool tileA{ false };
	bool tileB{ false };
	bool tileC{ false };
	bool tileD{ false };
	bool tileE{ false };
	bool tileF{ false };
};
