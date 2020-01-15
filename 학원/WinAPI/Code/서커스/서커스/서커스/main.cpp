#include<windows.h>
#include "GameManager.h"
#include "DrawManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("��Ŀ��");
void CALLBACK GameFrame(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

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

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024,768, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);


	GameManager::Instance()->Init();
	DrawManager::Instance()->Init(GetDC(hWnd));

	while (true) 
	{ 
		// �޽���ť�� �޽����� ������ �޽��� ó�� 
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{ 
			if (Message.message == WM_QUIT) break; 
			TranslateMessage(&Message); 
			DispatchMessage(&Message); 
		} 
		else 
		{ 
			//�޼����� ������ ������Ʈ�� �����Ѵ�.
			GameManager::Instance()->Update(GetDC(hWnd),hWnd);
		} 
	} //���������� ������ ���ش�. 

	GameManager::Instance()->Release();
	DrawManager::Instance()->Release();


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
		case WM_KEYDOWN:
		{
			if (GetKeyState(VK_SPACE) & 0x8000)
			{
				GameManager::Instance()->Jump();
			}
		}
		return 0;

		case WM_CREATE:
		{
			
		}
		return 0;
		case WM_DESTROY:
		{
			
			PostQuitMessage(0);
		}
			return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));

}




void CALLBACK GameFrame(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	GameManager::Instance()->CreateEnemy();
}