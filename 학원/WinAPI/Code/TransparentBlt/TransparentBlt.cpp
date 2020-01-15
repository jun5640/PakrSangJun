#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); 
void CALLBACK AnimationTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TransparentBlt");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
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
			 
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, 
		NULL, (HMENU)NULL, hInstance, NULL); 

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) 										
	{
		TranslateMessage(&Message); 
		DispatchMessage(&Message); 
	}
	return (int)Message.wParam;
}

int xpos = 650;
int ypos = 50;
int Dir = 0;
int AnimationKeyFrame = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HDC hMemDC;
	HBITMAP hImage, hOldBitmap;
	int bx, by;
	BITMAP bit;
	

	switch (iMessage)
	{
	case WM_KEYDOWN:


		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hMemDC = CreateCompatibleDC(hdc); 
								  
		hImage = (HBITMAP)LoadImage(NULL, TEXT("image.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);

		GetObject(hImage, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;

		////원본 그대로
		////화면의 (50, 50) 위치에 원본 크기로 원본의 (0, 0) 위치부터 추출하여 그린다
		//BitBlt(hdc, 50, 50, bx, by, hMemDC, 0, 0, SRCCOPY);

		////투명처리
		////RGB(255, 0, 255)(핑크색)을 투명하게 만들고 그린다
		//TransparentBlt(hdc, 350, 50, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 0, 255));

		////투명처리와 부분그리기 
		////이번에는 왼쪽을 보고 있고 한발을 내딛은 캐릭터를 그린다

		TransparentBlt(hdc, xpos, ypos, bx / 4, by / 4,
			hMemDC, (bx / 4) * AnimationKeyFrame, (by / 4) * Dir, bx / 4, by / 4, RGB(255, 0, 255));
		AnimationKeyFrame++;

		if (AnimationKeyFrame >= 4)
		{
			AnimationKeyFrame = 0;
		}

		// 1열 아래 2열	위로 3열 왼쪽 4열 오른쪽

		SelectObject(hMemDC, hOldBitmap); 
		DeleteObject(hImage); 
		DeleteDC(hMemDC); 
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hWnd, 1);
		return 0;
	case WM_CREATE:
		SetTimer(hWnd, 1, 16, AnimationTimer);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void CALLBACK AnimationTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		Dir = 2;
		xpos -= 10;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		Dir = 3;
		xpos += 10;
	}
	if (GetKeyState(VK_UP) & 0x8000)
	{
		Dir = 1;
		ypos -= 10;
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		Dir = 0;
		ypos += 10;
	}

	InvalidateRect(hWnd, NULL, TRUE);
}