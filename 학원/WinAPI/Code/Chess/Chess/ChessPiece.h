#pragma once

#include "CommonFeature.h"

class ChessPiece
{
protected:
	int PieceType = -1;		//�ǽ� Ÿ��
	int TeamType = -1;
	TCHAR* m_tcImagePath;

public:
	TCHAR* GetImagePath() { return m_tcImagePath; }
	virtual void Process() = 0;	//ü�� ���� Ÿ�� �ش� ü���� Ŭ�� �Ͽ��� ��� �ߵ� �Ѵ�.
};

