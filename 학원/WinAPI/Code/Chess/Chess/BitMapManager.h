#pragma once
#pragma comment(lib,"Msimg32.lib");

#include "SingletonBase.h"
#include "TileInfo.h"


class BitMapManager : public SingletonBase<BitMapManager>
{
protected:

	//vector<BitMapInfo> m_vBitMapInfo;
	vector<TileInfo> m_vTileInfo;

	HBITMAP myBitmap, oldBitmap, hImage, hOldBitmap;

	int preSource = -1;
	TCHAR* tilecolorPath;

	TileInfo * FirstClick = nullptr;
public:
	int DelayTime = 0;

	BitMapManager() {};
	~BitMapManager() {};

	void DrawAllTile(HDC hdc, HDC MemDC, HINSTANCE hInst)
	{

		vector<TileInfo>::iterator iter = m_vTileInfo.begin();

		for (iter; iter != m_vTileInfo.end(); iter++)
		{
			

			if (iter->TileColorType == BROWNTILE)
			{
				tilecolorPath = (TCHAR*)TEXT("Res/block01.bmp");
				
			}
			else
			{
				tilecolorPath = (TCHAR*)TEXT("Res/block0.bmp");
			}

			hImage = (HBITMAP)LoadImage(NULL, tilecolorPath,
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			hOldBitmap = (HBITMAP)SelectObject(MemDC, hImage);
			
			TransparentBlt(hdc, iter->m_rt.left,iter->m_rt.top, iter->width,iter->width, MemDC, 0, 0, iter->width, iter->width, RGB(255, 0, 255));

			SelectObject(MemDC, hOldBitmap);
			DeleteObject(hImage);
			
			if (iter->m_piece != nullptr)
			{
				hImage = (HBITMAP)LoadImage(NULL, iter->m_piece->GetImagePath(),
					IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

				hOldBitmap = (HBITMAP)SelectObject(MemDC, hImage);

				TransparentBlt(hdc, iter->m_rt.left, iter->m_rt.top, iter->width, iter->width, MemDC, 0, 0, iter->width, iter->width, RGB(255, 0, 255));

				SelectObject(MemDC, hOldBitmap);
				DeleteObject(hImage);
			}
		}

		DeleteDC(MemDC);
	}

	void RegisterTileInfo(TileInfo info)
	{
		m_vTileInfo.push_back(info);
	}

	static BitMapManager* Instance()
	{
		if (_Instance == nullptr)
		{
			_Instance = new BitMapManager;
		}
		return _Instance;
	}

	void TileSelectCheck(int x, int y)
	{
		POINT pt;
		pt.x = x;
		pt.y = y;

		vector<TileInfo>::iterator iter = m_vTileInfo.begin();

		for (iter; iter != m_vTileInfo.end(); iter++)
		{
			if (PtInRect(&(iter->m_rt), pt))
			{
				if (iter->m_piece != nullptr)
				{
					if (FirstClick == nullptr)
					{
						FirstClick = &(*iter);
						break;
					}
					else
					{
						//
						// 같은 팀이 아닐때 혹은 빈곳 일때의 조건문 해당 이동쪽에 상대 말이 있을경우 할댕해제도 해줘야 한다.
						//
						if (iter->m_piece != FirstClick->m_piece)
						{
							iter->m_piece = FirstClick->m_piece;
							FirstClick->m_piece = nullptr;
						}
					}
				}
			}
		}
	}
};

