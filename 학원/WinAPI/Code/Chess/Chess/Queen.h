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

	bool Process(ChessPiece* other, int deltaX, int deltaY) 
	{
		int otherTeam = -1;
		bool result = false;

		if (deltaX < 0) deltaX = deltaX * -1;
		if (deltaY < 0) deltaY = deltaY * -1;

		if (other != nullptr)
		{
			otherTeam = other->GetTeamType();
		}

		if (otherTeam != TeamType && (deltaX == deltaY || (deltaX == 0 || deltaY == 0))) result = true;

		return result;
	}
};

