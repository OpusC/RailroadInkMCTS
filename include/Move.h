#pragma once
#include "Tiles.h"
#include <vector>

struct Move
{
	Tile tile;
	int x;
	int y;
};

using Turn = std::vector<Move>;
