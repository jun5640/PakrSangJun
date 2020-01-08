#pragma once


#include "BitMapInfo.h"
#include "SingletonBase.h"
#include <vector>
#include "resource.h"

using namespace std;

class BitMapManager : public SingletonBase<BitMapManager>
{
protected:

	vector<BitMapInfo> m_vBitMapInfo;

	HBITMAP myBitmap, oldBitmap;

	int preSource = -1;

public:
	int DelayTime = 0;

	BitMapManager() {};
	~BitMapManager() {};

	void VectorClear()
	{
		m_vBitMapInfo.clear();
	}

	int GetDrawDefine(int index)
	{
		return m_vBitMapInfo[index].m_idrawdefine;
	}

	void SetReverse(int index, bool value)
	{
		m_vBitMapInfo[index].m_bisreverse = value;
	}

	void DrawBitBlt(TCHAR* str, HDC hdc, HDC MemDC, HINSTANCE hInst)
	{
		vector<BitMapInfo>::iterator iter = m_vBitMapInfo.begin();

		for (iter; iter != m_vBitMapInfo.end(); iter++)
		{
			if (iter->m_tcstr == str)
			{
				SelectObject(MemDC, oldBitmap);
				DeleteObject(myBitmap);
		
				myBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(iter->m_idrawdefine));
				oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap);
				BitBlt(hdc, iter->m_ix, iter->m_iy, iter->m_iwidth, iter->m_iheight, MemDC, iter->m_isrcx, iter->m_isrcy, iter->m_dwrop);

				SelectObject(MemDC, oldBitmap);
				DeleteObject(myBitmap);
				DeleteDC(MemDC);
			}
		}

	}

	void DrawStretchBlt(TCHAR* str, HDC hdc, HDC MemDC, HINSTANCE hInst)
	{
		vector<BitMapInfo>::iterator iter = m_vBitMapInfo.begin();

		for (iter; iter != m_vBitMapInfo.end(); iter++)
		{
			if (iter->m_tcstr == str)
			{
				SelectObject(MemDC, oldBitmap);
				DeleteObject(myBitmap);

				myBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(iter->m_idrawdefine));
				oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap);
				StretchBlt(hdc, iter->m_ix, iter->m_iy, iter->m_iwidth, iter->m_iheight, MemDC, iter->m_isrcx, iter->m_isrcy, iter->m_isrcwidth, iter->m_isrcheight, iter->m_dwrop);

				SelectObject(MemDC, oldBitmap);
				DeleteObject(myBitmap);
				DeleteDC(MemDC);
			}
		}

	}

	void Erase(TCHAR* str)
	{
		vector<BitMapInfo>::iterator iter = m_vBitMapInfo.begin();

		for (iter; iter != m_vBitMapInfo.end(); iter++)
		{
			if (iter->m_tcstr == str)
			{
				m_vBitMapInfo.erase(iter);
			}
		}
	}

	void DrawCard(HDC hdc, HDC MemDC, HINSTANCE hInst)
	{
		
		

		vector<BitMapInfo>::iterator iter = m_vBitMapInfo.begin();

		int drawdefine = -1;

		for (iter; iter != m_vBitMapInfo.end(); iter++)
		{
			if (iter->m_bisreverse)
			{
				drawdefine = iter->m_idrawdefine;
			}
			else
			{
				drawdefine = IDB_BITMAP2;
			}

			if (preSource != drawdefine)
			{
				if (preSource != -1)
				{
					SelectObject(MemDC, oldBitmap);
					DeleteObject(myBitmap);
				}

				
				myBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(drawdefine));
				oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap);
				BitBlt(hdc, iter->m_ix, iter->m_iy, iter->m_iwidth, iter->m_iheight, MemDC, iter->m_isrcx, iter->m_isrcy, iter->m_dwrop);

				preSource = drawdefine;
			}
			else
			{
				BitBlt(hdc, iter->m_ix, iter->m_iy, iter->m_iwidth, iter->m_iheight, MemDC, iter->m_isrcx, iter->m_isrcy, iter->m_dwrop);
			}
		}

		preSource = -1;
		SelectObject(MemDC, oldBitmap);
		DeleteObject(myBitmap);
		DeleteDC(MemDC);

		Sleep(DelayTime);
		DelayTime = 0;
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
		
		preSource = -1;
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

		preSource = -1;
		SelectObject(MemDC, oldBitmap);
		DeleteObject(myBitmap);
		DeleteDC(MemDC);
	}

	int CrashCheck(int x, int y, HWND hWnd)
	{
		int count = 0;
		vector<BitMapInfo>::iterator iter = m_vBitMapInfo.begin();
		for (iter; iter != m_vBitMapInfo.end(); iter++)
		{
			if (iter->CrashCheck(x, y) && !iter->m_bisreverse)
			{
				iter->m_bisreverse = true;
				return count;
			}
			count++;
		}

		return -1;
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

