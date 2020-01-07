#pragma once


#include "BitMapInfo.h"
#include <vector>

using namespace std;

class BitMapManager
{
protected:
	static BitMapManager* _Instance;

	vector<BitMapInfo> m_vBitMapInfo;

	HBITMAP myBitmap, oldBitmap;

	BitMapManager() {};
	BitMapManager(const BitMapManager&) {};
	~BitMapManager() {};

	int preSource = -1;

public:

	void Release()
	{
		delete _Instance;
	}

	void DrawAllBitBlt(HDC hdc,HDC MemDC, HINSTANCE hInst)
	{
		vector<BitMapInfo>::iterator iter = m_vBitMapInfo.begin();
		

		for (iter; iter != m_vBitMapInfo.end(); iter++)
		{
			if (preSource != iter->m_idrawdefine)
			{
				if (preSource != -1)
				{
					SelectObject(MemDC, oldBitmap);
					DeleteObject(myBitmap);
				}

				myBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(iter->m_idrawdefine));
				oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap);
				BitBlt(hdc, iter->m_ix, iter->m_iy, iter->m_iwidth, iter->m_iheight, MemDC, iter->m_isrcx, iter->m_isrcy, iter->m_dwrop);

				preSource = iter->m_idrawdefine;
			}
			else
			{
				BitBlt(hdc, iter->m_ix, iter->m_iy, iter->m_iwidth, iter->m_iheight, MemDC, iter->m_isrcx, iter->m_isrcy, iter->m_dwrop);
			}
		}
		
		SelectObject(MemDC, oldBitmap);
		DeleteObject(myBitmap);
		DeleteDC(MemDC);
	}

	void DrawAllStretchBlt(HDC hdc, HDC MemDC, HINSTANCE hInst)
	{
		vector<BitMapInfo>::iterator iter = m_vBitMapInfo.begin();

		for (iter; iter != m_vBitMapInfo.end(); iter++)
		{
			if (preSource != iter->m_idrawdefine)
			{
				if (preSource != -1)
				{
					SelectObject(MemDC, oldBitmap);
					DeleteObject(myBitmap);
				}
			
				myBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(iter->m_idrawdefine));
				oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap);
				StretchBlt(hdc, iter->m_ix, iter->m_iy, iter->m_iwidth, iter->m_iheight, MemDC, iter->m_isrcx, iter->m_isrcy, iter->m_isrcwidth, iter->m_isrcheight, iter->m_dwrop);
				
				preSource = iter->m_idrawdefine;
			}
			else
			{
				StretchBlt(hdc, iter->m_ix, iter->m_iy, iter->m_iwidth, iter->m_iheight, MemDC,iter->m_isrcx, iter->m_isrcy,iter->m_isrcwidth,iter->m_isrcheight, iter->m_dwrop);
			}
		}

		SelectObject(MemDC, oldBitmap);
		DeleteObject(myBitmap);
		DeleteDC(MemDC);
	}

	void CrashCheck(int x, int y, HWND hWnd)
	{
		vector<BitMapInfo>::iterator iter = m_vBitMapInfo.begin();
		for (iter; iter != m_vBitMapInfo.end(); iter++)
		{
			if (iter->CrashCheck(x, y))
			{
				MessageBox(hWnd, iter->m_tcstr, TEXT("MessageBox"), MB_OK);
			}
		}
	}

	void RegisterBitInfo(BitMapInfo info)
	{
		m_vBitMapInfo.push_back(info);
	}

	static BitMapManager* Instance()
	{
		if (_Instance == nullptr)
		{
			_Instance = new BitMapManager;
		}
		return _Instance;
	}
};

