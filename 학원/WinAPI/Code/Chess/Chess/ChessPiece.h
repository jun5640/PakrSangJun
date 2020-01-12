#pragma once

#include "CommonFeature.h"

class ChessPiece
{
protected:
	int PieceType = -1;		//피스 타입
	int TeamType = -1;
	TCHAR* m_tcImagePath;

public:
	TCHAR* GetImagePath() { return m_tcImagePath; }
	virtual void Process() = 0;	//체스 진행 타입 해당 체스를 클릭 하였을 경우 발동 한다.
};

