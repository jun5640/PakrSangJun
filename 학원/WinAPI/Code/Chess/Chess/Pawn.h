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

	bool Process(ChessPiece* other, int deltaX, int deltaY)
	{

		if (TeamType == BLACKTEAM)
		{
			deltaX = deltaX * -1;
			deltaY = deltaY * -1;
		}

		int otherTeam = -1;
		bool result = false;

		if (other != nullptr)
		{
			otherTeam = other->GetTeamType();
		}

		
		if (otherTeam == TeamType || deltaY > 2 || deltaY < 1 || deltaX > 1 || deltaX < -1) result = false;
			
		if (IsFirstMove)
		{
			if (deltaY == 2 && deltaX == 0  && other == nullptr)
			{
				IsFirstMove = false;
				result = true;
				Upgrade += deltaY;
			}
			else if (deltaY == 1 && deltaX == 0 && other == nullptr)
			{
				IsFirstMove = false;
				result = true;
				Upgrade += deltaY;
			}
			else if (deltaY == 1 && (deltaX == 1 || deltaX == -1))
			{
				if (other != nullptr)
				{
					IsFirstMove = false;
					result = true;
					Upgrade += deltaY;
				}
			}
		}
		else
		{
			if (deltaY == 2 && (deltaX == 1 || deltaX == -1)) result = false;
			if (deltaY == 2) result = false;

			if (deltaY == 1 && deltaX == 0 && other == nullptr )
			{
				result = true;
				Upgrade += deltaY;
			}
			else if (deltaY == 1 && (deltaX == 1 || deltaX == -1))
			{
				if (other != nullptr)
				{
					result = true;
					Upgrade += deltaY;
				}
			}
		}



		
		return result;
	};
};

