#include "Bitmap.h"
#include"resource.h"

Bitmap::Bitmap()
{
}

void Bitmap::Init(HDC hdc, HINSTANCE hInst)
{
	MemDC = CreateCompatibleDC(hdc);
	m_pMyBitMap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	m_pOldBitMap = (HBITMAP)SelectObject(MemDC, m_pMyBitMap);

	BITMAP Bit_Info;
	GetObject(m_pMyBitMap, sizeof(Bit_Info), &Bit_Info);
	m_size.cx = Bit_Info.bmWidth;
	m_size.cy = Bit_Info.bmHeight;
}
void Bitmap::Draw(HDC hdc, int x, int y)
{
	BitBlt(hdc, x, y, m_size.cx, m_size.cy, MemDC, 0, 0, SRCCOPY);
}

Bitmap::~Bitmap()
{
	SelectObject(MemDC, m_pOldBitMap);
	DeleteObject(m_pMyBitMap);
	DeleteDC(MemDC);
}
