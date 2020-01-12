#pragma once

#include "ChessPiece.h"

class Kinght : public ChessPiece
{
public:
	Kinght(int teamType)
	{
		TeamType = teamType;
		PieceType = KINGHT;

		if (TeamType == BLACKTEAM)
		{
			m_tcImagePath = (TCHAR*)BLACKKINGHTPATH;
		}
		else
		{
			m_tcImagePath = (TCHAR*)WHITEKINGHTPATH;
		}
	}

	void Process() {};
};

