#pragma once

#include "ChessPiece.h"

class Pawn : public ChessPiece
{
private:
	bool IsFirstMove = true;

public:
	Pawn(int teamType)
	{
		TeamType = teamType;
		PieceType = PAWN;

		if (TeamType == BLACKTEAM)
		{
			m_tcImagePath = (TCHAR*)BLACKPAWNPATH;
		}
		else
		{
			m_tcImagePath = (TCHAR*)WHITEPAWNPATH;
		}
	}

	void Process() {};
};

