#pragma once
#include "TileEnums.h"
struct BoardExit
{
	int boardX;
	int boardY;
	Direction exitDirection;
	ConnectionType connectionType;
};
