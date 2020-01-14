#pragma once

#include "CommonFeature.h"

class ChessPiece
{
protected:
	int PieceType = -1;		//�ǽ� Ÿ��
	int TeamType = -1;
	TCHAR* m_tcImagePath;
	int Upgrade = 0; // �����ڰ� ��Ÿ 6

public:
	int GetUpgrade() { return Upgrade; }
	TCHAR* GetImagePath() { return m_tcImagePath; }
	int GetTeamType() { return TeamType; }
	int GetPieceType() { return PieceType; }
	virtual bool Process(ChessPiece* other,int deltaX, int deltaY) = 0;	//ü�� ���� Ÿ�� �ش� ü���� Ŭ�� �Ͽ��� ��� �ߵ� �Ѵ�.
};

