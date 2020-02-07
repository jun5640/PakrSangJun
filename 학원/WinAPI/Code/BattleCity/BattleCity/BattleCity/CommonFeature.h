#pragma once

#include <Windows.h>
#include "BaseTile.h"

class MapToolTile
{
public:
	MapToolTile() {};
	~MapToolTile() {};
	BaseTile tileinfo;
	POINT position;
	bool IsSet = false;
};

#define TILEX 33
#define TILEY 25

#define ERASETILE 15