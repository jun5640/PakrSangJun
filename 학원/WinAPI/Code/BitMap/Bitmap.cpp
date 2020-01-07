#include "resource.h"
#include<windows.h>
#include "BitMapManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BitMap");



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{

	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int x;
	int y;

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);

		BitMapManager::Instance()->CrashCheck(x, y,hWnd);

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);


		//BitMapManager::Instance()->DrawAllBitBlt(hdc, CreateCompatibleDC(hdc), g_hInst);
		BitMapManager::Instance()->DrawAllStretchBlt(hdc, CreateCompatibleDC(hdc), g_hInst);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_CREATE:
		BitMapManager::Instance()->RegisterBitInfo(BitMapInfo(TEXT("DRAW1"), 100, 100, 145, 235, 0, 0, SRCCOPY, IDB_BITMAP1));
		BitMapManager::Instance()->RegisterBitInfo(BitMapInfo(TEXT("DRAW2"), 300, 100, 145, 235, 0, 0, SRCCOPY, IDB_BITMAP1));
		BitMapManager::Instance()->RegisterBitInfo(BitMapInfo(TEXT("DRAW3"), 100, 500, 100, 100, 0, 0, SRCCOPY, IDB_BITMAP2));
		break;
	case WM_DESTROY:
		BitMapManager::Instance()->Release();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
