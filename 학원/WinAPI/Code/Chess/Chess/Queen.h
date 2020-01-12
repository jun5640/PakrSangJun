#pragma once

#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
	Queen(int teamType)
	{
		TeamType = teamType;
		PieceType = QUEEN;

		if (TeamType == BLACKTEAM)
		{
			m_tcImagePath = (TCHAR*)BLACKQUEENPATH;
		}
		else
		{
			m_tcImagePath = (TCHAR*)WHITEQUEENPATH;
		}
	}

	void Process() {};
};

