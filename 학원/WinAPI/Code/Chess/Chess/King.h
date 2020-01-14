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

		if (otherTeam != TeamType && deltaX < 2  &&  deltaY < 2) result = true;

		return result;
	}
};

