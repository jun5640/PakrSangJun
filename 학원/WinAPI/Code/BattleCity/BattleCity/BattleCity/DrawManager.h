#pragma once
#pragma comment(lib,"Msimg32.lib")

#include "CommonFeature.h"
#include "SingletonBase.h"
#include "BaseTile.h"
#include "Player.h"
#include "Bullet.h"

class DrawManager : public SingletonBase<DrawManager>
{
private:

	HDC g_MemDC[5];
	HBITMAP g_hBitMap[5];
	HBITMAP g_hOld[5];
	HINSTANCE hInst;

	bool IsFirst = false;

	int CanvasX = 0;
	int CanvasY = 0;
public:

	~DrawManager()
	{
		DeleteDC(g_MemDC[0]);	//그려질놈
		DeleteDC(g_MemDC[1]);	// 백지 드로우 및 UI관련 드로우
		DeleteDC(g_MemDC[2]);	// 배경
		DeleteDC(g_MemDC[3]);	// 캐릭터 및 이팩트
		DeleteDC(g_MemDC[4]);	// 바닥  물,철 바닥 등등
	}

	void Init(HDC hdc)
	{
		g_MemDC[0] = CreateCompatibleDC(hdc);
		g_MemDC[1] = CreateCompatibleDC(g_MemDC[0]);
		g_MemDC[2] = CreateCompatibleDC(g_MemDC[0]);
		g_MemDC[3] = CreateCompatibleDC(g_MemDC[0]);	
		g_MemDC[4] = CreateCompatibleDC(g_MemDC[0]);
	}

	void SetCanvasSize(int x, int y)
	{
		CanvasX = x;
		CanvasY = y;
	}

	//
	//MoveToEx // 시작 LineTo End
	// 
	void DrawLine(POINT start_point, POINT end_point)
	{
		HPEN MyPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		HPEN OldPen = (HPEN)SelectObject(g_MemDC[0], MyPen);

		MoveToEx(g_MemDC[0], start_point.x, start_point.y, NULL);
		LineTo(g_MemDC[0], end_point.x, end_point.y);

		SelectObject(g_MemDC[0], OldPen);
		DeleteObject(MyPen);
	}

	void DrawUITEXT(int xpos,int ypos,TCHAR* msg,int size)
	{
		TextOut(g_MemDC[0],xpos , ypos, msg, size);
	}

	void DrawUIBmp(TCHAR* path, int xpos,int ypos, int width,int height)
	{
		g_hBitMap[1] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		g_hOld[1] = (HBITMAP)SelectObject(g_MemDC[1], g_hBitMap[1]);

		TransparentBlt(g_MemDC[0], xpos, ypos, width, height,
			g_MemDC[1], 0, 0, width, height, RGB(255, 0, 255));

		SelectObject(g_MemDC[1], g_hOld[1]);
		DeleteObject(g_hBitMap[1]);
	}

	void InitCanvas(HDC hdc)
	{
		g_hBitMap[0] = CreateCompatibleBitmap(hdc, CanvasX, CanvasY);
		g_hOld[0] = (HBITMAP)SelectObject(g_MemDC[0], g_hBitMap[0]);
	}

	void DrawBmp(MapToolTile tile)
	{
		g_hBitMap[2] = (HBITMAP)LoadImage(NULL, tile.tileinfo.GetImagePath(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		g_hOld[2] = (HBITMAP)SelectObject(g_MemDC[2], g_hBitMap[2]);

		TransparentBlt(g_MemDC[0], tile.position.x, tile.position.y, tile.tileinfo.GetWidth(), tile.tileinfo.GetHeight(),
			g_MemDC[2], 0, 0, tile.tileinfo.GetScrWidth(), tile.tileinfo.GetScrHeight(), RGB(255, 0, 255));

		SelectObject(g_MemDC[2], g_hOld[2]);
		DeleteObject(g_hBitMap[2]);
	}

	void DrawFloor(MapToolTile tile)
	{
		g_hBitMap[4] = (HBITMAP)LoadImage(NULL, tile.tileinfo.GetImagePath(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		g_hOld[4] = (HBITMAP)SelectObject(g_MemDC[4], g_hBitMap[4]);

		TransparentBlt(g_MemDC[0], tile.position.x, tile.position.y, tile.tileinfo.GetWidth(), tile.tileinfo.GetHeight(),
			g_MemDC[4], 0, 0, tile.tileinfo.GetScrWidth(), tile.tileinfo.GetScrHeight(), RGB(255, 0, 255));

		SelectObject(g_MemDC[4], g_hOld[4]);
		DeleteObject(g_hBitMap[4]);
	}

	void DrawPlayer(BasePlayer* player)
	{
		g_hBitMap[3] = (HBITMAP)LoadImage(NULL, player->GetAnimationPath(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		g_hOld[3] = (HBITMAP)SelectObject(g_MemDC[3], g_hBitMap[3]);

		TransparentBlt(g_MemDC[0], player->GetPosition().x, player->GetPosition().y, player->GetWidth(), player->GetHeight(),
			g_MemDC[3], 0, 0, player->GetSCRWidth(), player->GetSCRHeight(), RGB(255, 0, 255));

		SelectObject(g_MemDC[3], g_hOld[3]);
		DeleteObject(g_hBitMap[3]);
	}

	void DrawBullet(Bullet* bullet)
	{
		if (bullet == nullptr) return;

		g_hBitMap[3] = (HBITMAP)LoadImage(NULL, bullet->GetAnimationPath(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		g_hOld[3] = (HBITMAP)SelectObject(g_MemDC[3], g_hBitMap[3]);

		TransparentBlt(g_MemDC[0], bullet->GetPosition().x, bullet->GetPosition().y, bullet->GetWidth(), bullet->GetHeight(),
			g_MemDC[3], 0, 0, bullet->GetSCRWidth(), bullet->GetSCRHeight(), RGB(255, 0, 255));

		SelectObject(g_MemDC[3], g_hOld[3]);
		DeleteObject(g_hBitMap[3]);
	}

	void DrawWhite(HDC hdc)
	{
		InitCanvas(hdc);

		g_hBitMap[1] = (HBITMAP)LoadImage(NULL, TEXT("BattleCity/white.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		g_hOld[1] = (HBITMAP)SelectObject(g_MemDC[1], g_hBitMap[1]);

		TransparentBlt(g_MemDC[0], 0, 0, CanvasX, CanvasY,
			g_MemDC[1], 0, 0, 64, 64, RGB(255, 0, 255));

		SelectObject(g_MemDC[1], g_hOld[1]);
		DeleteObject(g_hBitMap[1]);

		DrawCanvas(hdc);
	}

	void DrawGray(HDC hdc)
	{
		g_hBitMap[1] = (HBITMAP)LoadImage(NULL, TEXT("BattleCity/gray.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		g_hOld[1] = (HBITMAP)SelectObject(g_MemDC[1], g_hBitMap[1]);

		TransparentBlt(g_MemDC[0], TILEX*19, 0, 200, CanvasY,
			g_MemDC[1], 0, 0, 64, 64, RGB(255, 0, 255));

		SelectObject(g_MemDC[1], g_hOld[1]);
		DeleteObject(g_hBitMap[1]);
	}

	void DrawCanvas(HDC hdc)
	{
		BitBlt(hdc, 0, 0, CanvasX, CanvasX, g_MemDC[0], 0, 0, SRCCOPY);

		SelectObject(g_MemDC[0], g_hOld[0]);
		DeleteObject(g_hBitMap[0]);
	}
};

