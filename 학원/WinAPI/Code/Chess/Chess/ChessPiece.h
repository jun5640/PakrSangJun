#pragma once

#include "CommonFeature.h"

class ChessPiece
{
protected:
	int PieceType = -1;		//피스 타입
	int TeamType = -1;
	TCHAR* m_tcImagePath;
	int Upgrade = 0; // 변신자격 델타 6

public:
	int GetUpgrade() { return Upgrade; }
	TCHAR* GetImagePath() { return m_tcImagePath; }
	int GetTeamType() { return TeamType; }
	int GetPieceType() { return PieceType; }
	virtual bool Process(ChessPiece* other,int deltaX, int deltaY) = 0;	//체스 진행 타입 해당 체스를 클릭 하였을 경우 발동 한다.
};

