#pragma once

#include "SingletonBase.h"
#include "BitMapManager.h"
#include "resource.h"

#include<time.h>

#define MAX_CARD 14
#define ENDGAME 7

class GameManager : public SingletonBase<GameManager>
{

private:

	vector<BitMapInfo> m_vBitMapInfos;
	bool RandomCheck[14] = { false };

	int FirstClick = -1;
	int SecondClick = -1;

	int FindSameCard = 0;

	bool IsReverseReset = false;

public:

	GameManager()
	{
		m_vBitMapInfos.push_back(BitMapInfo(TEXT("1"), 100, 100, 145, 235, 0, 0, SRCCOPY, IDB_BITMAP4));
		m_vBitMapInfos.push_back(BitMapInfo(TEXT("1"), 100, 100, 145, 235, 0, 0, SRCCOPY, IDB_BITMAP4));
		m_vBitMapInfos.push_back(BitMapInfo(TEXT("2"), 100, 100, 145, 235, 0, 0, SRCCOPY, IDB_BITMAP5));
		m_vBitMapInfos.push_back(BitMapInfo(TEXT("2"), 100, 100, 145, 235, 0, 0, SRCCOPY, IDB_BITMAP5));
		m_vBitMapInfos.push_back(BitMapInfo(TEXT("3"), 100, 100, 145, 235, 0, 0, SRCCOPY, IDB_BITMAP6));
		m_vBitMapInfos.push_back(BitMapInfo(TEXT("3"), 100, 100, 145, 235, 0, 0, SRCCOPY, IDB_BITMAP6));
		m_vBitMapInfos.push_back(BitMapInfo(TEXT("4"), 100, 100, 145, 235, 0, 0, SRCCOPY, IDB_BITMAP7));
		m_vBitMapInfos.push_back(BitMapInfo(TEXT("4"), 100, 100, 145, 235, 0, 0, SRCCOPY, IDB_BITMAP7));
		m_vBitMapInfos.push_back(BitMapInfo(TEXT("5"), 100, 100, 145, 235, 0, 0, SRCCOPY, IDB_BITMAP8));
		m_vBitMapInfos.push_back(BitMapInfo(TEXT("5"), 100, 100, 145, 235, 0, 0, SRCCOPY, IDB_BITMAP8));
		m_vBitMapInfos.push_back(BitMapInfo(TEXT("6"), 100, 100, 145, 235, 0, 0, SRCCOPY, IDB_BITMAP9));
		m_vBitMapInfos.push_back(BitMapInfo(TEXT("6"), 100, 100, 145, 235, 0, 0, SRCCOPY, IDB_BITMAP9));
		m_vBitMapInfos.push_back(BitMapInfo(TEXT("7"), 100, 100, 145, 235, 0, 0, SRCCOPY, IDB_BITMAP10));
		m_vBitMapInfos.push_back(BitMapInfo(TEXT("7"), 100, 100, 145, 235, 0, 0, SRCCOPY, IDB_BITMAP10));
	}

	void Init()
	{
		FindSameCard = 0;
		FirstClick = -1;
		SecondClick = -1;

		IsReverseReset = false;

		for (int i = 0; i < 14; i++)
		{
			RandomCheck[i] = false;
		}

		BitMapManager::Instance()->VectorClear();

		srand((unsigned int)time(NULL));

		int count = 0;

		while (true)
		{
			int random = rand() % 14;

			if (RandomCheck[random] == false)
			{
				

				if (count == 0)
				{
					m_vBitMapInfos[random].m_ix = 0;
					m_vBitMapInfos[random].m_iy = 0;
				}
				else
				{
					m_vBitMapInfos[random].m_ix = 200 * (count % 7);
					m_vBitMapInfos[random].m_iy = 300 * (count / 7);
				}	

				BitMapManager::Instance()->RegisterBitInfo(m_vBitMapInfos[random]);

				count++;
				RandomCheck[random] = true;

				if (count == MAX_CARD) break;
			}
		}
	}


	void CrashCheck(int x, int y, HWND hWnd)
	{
		if (FirstClick == -1)
		{
			FirstClick = BitMapManager::Instance()->CrashCheck(x, y, hWnd);
		}
		else
		{
			SecondClick = BitMapManager::Instance()->CrashCheck(x, y, hWnd);

			

			if (SecondClick == -1)
			{
				return;
			}
			else if (BitMapManager::Instance()->GetDrawDefine(SecondClick) == BitMapManager::Instance()->GetDrawDefine(FirstClick))
			{
				FindSameCard++;

				FirstClick = -1;
				SecondClick = -1;

				if (FindSameCard == ENDGAME)
				{
					if (MessageBox(hWnd, TEXT("Game Clear"), TEXT("Game Clear"), MB_OKCANCEL) == IDOK)
					{
						Init();
					}
					else
					{
						DestroyWindow(hWnd);
					}
				}
			}
			else
			{
				IsReverseReset = true;			
				BitMapManager::Instance()->DelayTime = 1000;
			}

		}

	}

	void ReverseReset(HWND hWnd)
	{
		if (IsReverseReset)
		{
			BitMapManager::Instance()->SetReverse(SecondClick, false);
			BitMapManager::Instance()->SetReverse(FirstClick, false);

			
			FirstClick = -1;
			SecondClick = -1;

			InvalidateRect(hWnd, NULL, true);
		}
		else
		{

		}
		IsReverseReset = false;
	}
};

