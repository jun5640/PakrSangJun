#pragma once
#pragma comment(lib,"Msimg32.lib")

#include "CommonFeature.h"
#include "CustomObject.h"
#include "SingletonBase.h"


class DrawManager : public SingletonBase<DrawManager>
{
private:

	/*EMPTY 0
	PLAYER 3
	ENEMY  2
	BACKGROUND 1*/

	HDC g_MemDC[4];
	HBITMAP g_hBitMap[4];
	HBITMAP g_hOld[4];
	HINSTANCE hInst;

	bool IsFirst = false;

public:

	~DrawManager()
	{

		
	

		DeleteDC(g_MemDC[0]);
		DeleteDC(g_MemDC[1]);
		DeleteDC(g_MemDC[2]);
		DeleteDC(g_MemDC[3]);
	}

	void Init(HDC hdc)
	{
		g_MemDC[0] = CreateCompatibleDC(hdc);
		g_MemDC[1] = CreateCompatibleDC(g_MemDC[0]);
		g_MemDC[2] = CreateCompatibleDC(g_MemDC[0]);
		g_MemDC[3] = CreateCompatibleDC(g_MemDC[0]);

		
	}

	void Draw(HDC hdc, vector<CustomObject*>::iterator begin, vector<CustomObject*>::iterator end)
	{
		g_hBitMap[0] = CreateCompatibleBitmap(hdc, 1024, 768);
		g_hOld[0] = (HBITMAP)SelectObject(g_MemDC[0], g_hBitMap[0]);

		vector<CustomObject*>::iterator iter;

		for (iter = begin; iter != end; iter++)
		{
			if ((*iter)->GetType() == BACKGROUND)
			{
				g_hBitMap[1] = (HBITMAP)LoadImage(NULL, (*iter)->GetAnimationPath(),IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				g_hOld[1] = (HBITMAP)SelectObject(g_MemDC[1], g_hBitMap[1]);


				TransparentBlt(g_MemDC[0], (*iter)->GetXpos(), (*iter)->GetYpos(), (*iter)->GetWidth(), (*iter)->GetHeight(),
					g_MemDC[1], (*iter)->GetSCRXpos(), (*iter)->GetSCRYpos(), (*iter)->GetSCRWidth(), (*iter)->GetSCRHeight(), RGB(255, 0, 255));
				//TransparentBlt(g_MemDC[0], 생성위치 x, 생성 위치y, 생성 크기, 생성 높이, g_MemDC[1], 0, 0, 원본이미지 크기 어디까지 짜를건지, 원본이미지 높이 어디까지 짜를건지, RGB(255, 0, 255));

				SelectObject(g_MemDC[1], g_hOld[1]);
				DeleteObject(g_hBitMap[1]);
			}
		}

		for (iter = begin; iter != end; iter++)
		{
			if ((*iter)->GetType() == ENEMY)
			{
				g_hBitMap[2] = (HBITMAP)LoadImage(NULL, (*iter)->GetAnimationPath(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				g_hOld[2] = (HBITMAP)SelectObject(g_MemDC[2], g_hBitMap[2]);


				TransparentBlt(g_MemDC[0], (*iter)->GetXpos(), (*iter)->GetYpos(), (*iter)->GetWidth(), (*iter)->GetHeight(),
					g_MemDC[2], (*iter)->GetSCRXpos(), (*iter)->GetSCRYpos(), (*iter)->GetSCRWidth(), (*iter)->GetSCRHeight(), RGB(255, 0, 255));
				//TransparentBlt(g_MemDC[0], 생성위치 x, 생성 위치y, 생성 크기, 생성 높이, g_MemDC[1], 0, 0, 원본이미지 크기 어디까지 짜를건지, 원본이미지 높이 어디까지 짜를건지, RGB(255, 0, 255));

				SelectObject(g_MemDC[2], g_hOld[2]);
				DeleteObject(g_hBitMap[2]);
			}
		}

		for (iter = begin; iter != end; iter++)
		{
			if ((*iter)->GetType() == PLAYER)
			{
				g_hBitMap[3] = (HBITMAP)LoadImage(NULL, (*iter)->GetAnimationPath(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				g_hOld[3] = (HBITMAP)SelectObject(g_MemDC[3], g_hBitMap[3]);


				TransparentBlt(g_MemDC[0], (*iter)->GetXpos(), (*iter)->GetYpos(), (*iter)->GetWidth(), (*iter)->GetHeight(),
					g_MemDC[3], (*iter)->GetSCRXpos(), (*iter)->GetSCRYpos(), (*iter)->GetSCRWidth(), (*iter)->GetSCRHeight(), RGB(255, 0, 255));
				//TransparentBlt(g_MemDC[0], 생성위치 x, 생성 위치y, 생성 크기, 생성 높이, g_MemDC[1], 0, 0, 원본이미지 크기 어디까지 짜를건지, 원본이미지 높이 어디까지 짜를건지, RGB(255, 0, 255));

				//BitBlt(hdc, 0, 0, 1024, 768, g_MemDC[0], 0, 0, SRCCOPY);

				SelectObject(g_MemDC[3], g_hOld[3]);
				DeleteObject(g_hBitMap[3]);
				
			}
		}

		BitBlt(hdc, 0, 0, 1024, 768, g_MemDC[0], 0, 0, SRCCOPY);	
	}
};

