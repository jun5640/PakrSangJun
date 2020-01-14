#pragma once

#include "SingletonBase.h"
#include "BitMapManager.h"
#include "TileInfo.h"
#include "Pawn.h"
#include "Rook.h"
#include "Kinght.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"

#define MAX_CARD 14
#define ENDGAME 7


#define BLACKTEAM 0
#define WHITETEAM 1

//
// ∏ ≈©±‚ 8x8
//
class GameManager : public SingletonBase<GameManager>
{

private:

	TCHAR* tilecolorPath;
	int GameTurn = WHITETEAM;

public:

	GameManager()
	{
		
	}

	void Init()
	{
		int xpos = 0;
		int ypos = 0;
		HBITMAP hImage;

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				TileInfo Info;
				if ((i + j) % 2 == 0)
				{
					Info.TileColorType = BROWNTILE;
				}
				else
				{
					Info.TileColorType = WHITETILE;
				}

				

				if (Info.TileColorType == BROWNTILE)
				{
					tilecolorPath = (TCHAR*)TEXT("Res/block01.bmp");

				}
				else
				{
					tilecolorPath = (TCHAR*)TEXT("Res/block0.bmp");
				}

				hImage = (HBITMAP)LoadImage(NULL, tilecolorPath,
					IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

				BITMAP bit;

				GetObject(hImage, sizeof(BITMAP), &bit);
				int bx = bit.bmWidth;
				int by = bit.bmHeight;

				Info.m_rt.left = j * bx;
				Info.m_rt.top = i * by;
				Info.m_rt.right = j * bx + bx;
				Info.m_rt.bottom = i * by + by;
				Info.width = bx;
				Info.height = by;

				if (i == 0)
				{
					if (j == 0 || j == 7)
					{
						Info.m_piece = new Rook(BLACKTEAM);
					}
					else if (j == 1 || j == 6)
					{
						Info.m_piece = new Kinght(BLACKTEAM);
					}
					else if (j == 2 || j == 5)
					{
						Info.m_piece = new Bishop(BLACKTEAM);
					}
					else if (j == 3)
					{
						Info.m_piece = new Queen(BLACKTEAM);
					}
					else
					{
						Info.m_piece = new King(BLACKTEAM);
					}
				}
				else if (i == 1)
				{
					Info.m_piece = new Pawn(BLACKTEAM);
				}
				else if (i == 6)
				{
					Info.m_piece = new Pawn(WHITETEAM);
				}
				else if (i == 7)
				{
					if (j == 0 || j == 7)
					{
						Info.m_piece = new Rook(WHITETEAM);
					}
					else if (j == 1 || j == 6)
					{
						Info.m_piece = new Kinght(WHITETEAM);
					}
					else if (j == 2 || j == 5)
					{
						Info.m_piece = new Bishop(WHITETEAM);
					}
					else if (j == 3)
					{
						Info.m_piece = new King(WHITETEAM);
					}
					else
					{
						Info.m_piece = new Queen(WHITETEAM);
					}
				}
				BitMapManager::Instance()->RegisterTileInfo(Info);
			}
		}
		

	}


	void CrashCheck(int x, int y, HWND hWnd)
	{
		BitMapManager::Instance()->TileSelectCheck(x, y, GameTurn);
	}

	void InitSelect()
	{
		BitMapManager::Instance()->InitSelect();
	}

	void ChangeTurn()
	{
		if (GameTurn == WHITETEAM)
		{
			GameTurn = BLACKTEAM;
		}
		else
		{
			GameTurn = WHITETEAM;
		}
	}

	
};

