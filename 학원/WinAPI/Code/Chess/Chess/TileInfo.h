#pragma once

#include "ChessPiece.h"

class TileInfo
{
public:
	RECT m_rt;
	int width;
	int height;
	ChessPiece * m_piece = nullptr;
	int TileColorType = -1;
	void Draw() {};
};

