#pragma once

#include <Windows.h>

class BitMapInfo
{
public:

	TCHAR * m_tcstr;
	int m_ix;
	int m_iy;
	int m_iwidth;
	int m_iheight;
	int m_isrcx;
	int m_isrcy;
	int m_isrcwidth;
	int m_isrcheight;
	DWORD m_dwrop;
	int m_idrawdefine;

	BitMapInfo(TCHAR* str,int x, int y, int width, int height, int srcx, int srcy,int srcwidth,int srcheight, DWORD dwrop,int drawdefine)
	{
		m_tcstr = str;
		m_ix = x;
		m_iy = y;
		m_iwidth = width;
		m_iheight = height;
		m_isrcx = srcx;
		m_isrcy = srcy;
		m_isrcwidth = srcwidth;
		m_isrcheight = srcheight;
		m_dwrop = dwrop;
		m_idrawdefine = drawdefine;
	}
	BitMapInfo(TCHAR* str, int x, int y, int width, int height, int srcx, int srcy, DWORD dwrop,int drawdefine)
	{
		m_tcstr = str;
		m_ix = x;
		m_iy = y;
		m_iwidth = width;
		m_iheight = height;
		m_isrcx = srcx;
		m_isrcy = srcy;
		m_isrcwidth = width;
		m_isrcheight = height;
		m_dwrop = dwrop;
		m_idrawdefine = drawdefine;
	}
	bool CrashCheck(int x, int y)
	{
		if (x > m_ix && x < m_ix + m_iwidth && y > m_iy && y < m_iy + m_iheight) return true;
		else return false;
	}
};

