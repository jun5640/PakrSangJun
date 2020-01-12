#pragma once

#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
	Rook(int teamType)
	{
		TeamType = teamType;
		PieceType = ROOK;

		if (TeamType == BLACKTEAM)
		{
			m_tcImagePath = (TCHAR*)BLACKROOKPATH;
		}
		else
		{
			m_tcImagePath = (TCHAR*)WHITEROOKPATH;
		}
	}

	void Process() {};
};

