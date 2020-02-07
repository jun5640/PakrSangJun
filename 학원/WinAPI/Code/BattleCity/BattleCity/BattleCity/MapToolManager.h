#pragma once

#include "SingletonBase.h"
#include "CommonFeature.h"
#include "DrawManager.h"
#include "BaseTile.h"
#include "FileManager.h"



class MapToolManager : public SingletonBase<MapToolManager>
{
	// 19x19 Å×ÀÌºí
	int m_iXLength = 19;
	int m_iYLength = 19;

	bool m_IsStart = false;

	BaseTile tiles[15];
	BaseTile SelectTile; 

	MapToolTile TileInfos[19][19];

	bool EraseTile = false;
public:
	
	MapToolManager() {};
	~MapToolManager() {};

	void InIt()
	{
		tiles[0] = BaseTile((TCHAR*)TEXT("BattleCity/block00.bmp"));
		tiles[0].SetIsDestory(true);
		tiles[0].SetIsMove(false);
		tiles[1] = BaseTile((TCHAR*)TEXT("BattleCity/block01.bmp"));
		tiles[1].SetIsDestory(true);
		tiles[1].SetIsMove(false);
		tiles[2] = BaseTile((TCHAR*)TEXT("BattleCity/block02.bmp"));
		tiles[2].SetIsDestory(true);
		tiles[2].SetIsMove(false);
		tiles[3] = BaseTile((TCHAR*)TEXT("BattleCity/block03.bmp"));
		tiles[3].SetIsDestory(true);
		tiles[3].SetIsMove(false);
		tiles[4] = BaseTile((TCHAR*)TEXT("BattleCity/block04.bmp"));
		tiles[4].SetIsDestory(true);
		tiles[4].SetIsMove(false);
		tiles[5] = BaseTile((TCHAR*)TEXT("BattleCity/block05.bmp"));
		tiles[5].SetIsDestory(false);
		tiles[5].SetIsMove(true);
		tiles[5].SetIsFloor(true);
		tiles[6] = BaseTile((TCHAR*)TEXT("BattleCity/block06.bmp"));
		tiles[6].SetIsDestory(false);
		tiles[6].SetIsMove(true);
		tiles[6].SetIsTop(true);
		tiles[7] = BaseTile((TCHAR*)TEXT("BattleCity/block07.bmp"));
		tiles[7].SetIsDestory(false);
		tiles[7].SetIsMove(false);
		tiles[7].SetIsFloor(true);
		tiles[8] = BaseTile((TCHAR*)TEXT("BattleCity/block08.bmp"));
		tiles[8].SetIsDestory(false);
		tiles[8].SetIsMove(false);
		tiles[9] = BaseTile((TCHAR*)TEXT("BattleCity/block09.bmp"));
		tiles[9].SetIsDestory(false);
		tiles[9].SetIsMove(false);
		tiles[10] = BaseTile((TCHAR*)TEXT("BattleCity/block10.bmp"));
		tiles[10].SetIsDestory(false);
		tiles[10].SetIsMove(false);
		tiles[11] = BaseTile((TCHAR*)TEXT("BattleCity/block11.bmp"));
		tiles[11].SetIsDestory(false);
		tiles[11].SetIsMove(false);
		tiles[12] = BaseTile((TCHAR*)TEXT("BattleCity/block12.bmp"));
		tiles[12].SetIsDestory(false);
		tiles[12].SetIsMove(false);
		tiles[13] = BaseTile((TCHAR*)TEXT("BattleCity/block13.bmp"));
		tiles[13].SetIsDestory(true);
		tiles[13].SetIsMove(false);
		tiles[14] = BaseTile((TCHAR*)TEXT("BattleCity/block14.bmp"));
		tiles[14].SetIsDestory(false);
		tiles[14].SetIsMove(false);

		POINT point;

		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				point.x = TILEX * i;
				point.y = TILEY * j;

				TileInfos[i][j].position = point;
				TileInfos[i][j].tileinfo.SetImagePath(nullptr);
			}
		}
	}

	void Save(HWND hWnd)
	{
		FileManager::Instance()->TileToData(TileInfos);
		FileManager::Instance()->Save(hWnd);
	}

	void Load(HWND hWnd)
	{
		FileManager::Instance()->Load(hWnd,TileInfos);
	}

	void TileInfoSet(int x, int y)
	{
		RECT rect;
		POINT pt;
		pt.x = x;
		pt.y = y;


		//if (SelectTile.GetWidth() == 0) return;

		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				rect.left = TileInfos[i][j].position.x;
				rect.right = TileInfos[i][j].position.x + 33;
				rect.top = TileInfos[i][j].position.y;
				rect.bottom = TileInfos[i][j].position.y + 25;

				if (PtInRect(&rect, pt))
				{
					if (EraseTile)
					{
						TileInfos[i][j].IsSet = false;
					}
					else
					{
						TileInfos[i][j].tileinfo = SelectTile;
						TileInfos[i][j].IsSet = true;
					}
				}
			}
		}
	}

	void DrawBmp()
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				if (TileInfos[i][j].IsSet)
				{
					if (TileInfos[i][j].IsSet)
					{
						DrawManager::Instance()->DrawBmp(TileInfos[i][j]);
					}
				}
			}
		}
	}

	void SetSelectTile(int value)
	{
		if (value == ERASETILE)
		{
			EraseTile = true;
		}
		else
		{
			EraseTile = false;
			SelectTile = tiles[value];
		}
	}

	void Update(HDC hdc)
	{
		if (!m_IsStart) return;

		DrawManager::Instance()->InitCanvas(hdc);
		DrawBmp();
		DrawLine(hdc);
		DrawManager::Instance()->DrawCanvas(hdc);
	}

	void SetMapToolStart(bool value,HDC hdc)
	{
		if (m_IsStart != value && !value)
		{
			DrawManager::Instance()->DrawWhite(hdc);
		}
		m_IsStart = value;
	}

	void DrawLine(HDC hdc)
	{
		POINT start1;
		POINT start2;
		POINT end1;
		POINT end2;

		for (int i = 0; i < 20; i++)
		{
			start1.x = 0;
			end1.x = TILEX * m_iXLength;
			start1.y = TILEY * i;
			end1.y = TILEY * i;

			start2.x = TILEX * i;
			end2.x = TILEX * i;
			start2.y = 0;
			end2.y = TILEY * m_iYLength;

			DrawManager::Instance()->DrawLine(start1, end1);
			DrawManager::Instance()->DrawLine(start2, end2);
		}
	}
};

