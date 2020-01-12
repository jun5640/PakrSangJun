#pragma once

#include "ChessPiece.h"

class King : public ChessPiece
{
public:
	King(int teamType)
	{
		TeamType = teamType;
		PieceType = KING;

		if (TeamType == BLACKTEAM)
		{
			m_tcImagePath = (TCHAR*)BLACKKINGPATH;
		}
		else
		{
			m_tcImagePath = (TCHAR*)WHITEKINGPATH;
		}
	}

	void Process() {};
};

