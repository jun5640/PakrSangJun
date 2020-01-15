#pragma once
#include<Windows.h>
class Bitmap
{
private:
	HDC		MemDC;
	HBITMAP	m_pMyBitMap;
	HBITMAP	m_pOldBitMap;
	SIZE	m_size;
public:
	Bitmap();
	void Init(HDC hdc, HINSTANCE hInst);
	void Draw(HDC hdc, int x, int y);
	~Bitmap();
};

