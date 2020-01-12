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

	void Process() {};
};

