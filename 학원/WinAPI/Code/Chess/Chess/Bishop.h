#pragma once

#include "ChessPiece.h"

class Bishop : public ChessPiece
{
public:
	Bishop(int teamType)
	{
		TeamType = teamType;
		PieceType = BISHOP;

		if (TeamType == BLACKTEAM)
		{
			m_tcImagePath = (TCHAR*)BLACKBISHOPPATH;
		}
		else
		{
			m_tcImagePath = (TCHAR*)WHITEBISHOPPATH;
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

		if (otherTeam != TeamType && deltaX == deltaY) result = true;

		return result;
	}
};

