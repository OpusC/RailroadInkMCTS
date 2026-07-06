#include "SpecialTileUsage.h"
#include "TileEnums.h"

bool SpecialTileUsage::isUsed(TileType tile) const
{
	switch (tile) {
	case (TileType::Special1):
		return tileA;
	case (TileType::Special2):
		return tileB;
	case (TileType::Special3):
		return tileC;
	case (TileType::Special4):
		return tileD;
	case (TileType::Special5):
		return tileE;
	case (TileType::Special6):
		return tileF;
	default:
		return false;
	}
}

void SpecialTileUsage::markUsed(TileType tile)
{
	switch (tile) {

	case Special1:
		tileA = true;
		break;
	case Special2:
		tileB = true;
		break;
	case Special3:
		tileC = true;
		break;
	case Special4:
		tileD = true;
		break;
	case Special5:
		tileE = true;
		break;
	case Special6:
		tileF = true;
		break;
	default:
		break;
	}
}

bool SpecialTileUsage::allUsed() const
{
	return tileA && tileB && tileC && tileD && tileE && tileF;
}
