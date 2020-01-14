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

	bool Process(ChessPiece* other, int deltaX, int deltaY) 
	{
		int otherTeam = -1;
		bool result = false;



		if (other != nullptr)
		{
			otherTeam = other->GetTeamType();
		}

		if (otherTeam != TeamType && (deltaX == 0 || deltaY == 0)) result = true;

		return result;
	}
};

