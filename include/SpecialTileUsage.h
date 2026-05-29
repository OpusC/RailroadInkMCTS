#pragma once

#include "TileEnums.h"
class SpecialTileUsage
{
  public:
	bool isUsed(
	  TileType tile) const;// TODO: have isSpecialTile in TileType enum/class
	void markUsed(TileType tile);
	bool allUsed() const;

  private:
	bool tileA{ false };
	bool tileB{ false };
	bool tileC{ false };
	bool tileD{ false };
	bool tileE{ false };
	bool tileF{ false };
};
