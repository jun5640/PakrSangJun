#include<windows.h>
#include "resource.h"
#include "MapToolManager.h"
#include "GameManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CreateRadioButton(HWND hWnd);
void RadioButtonUpdate(WPARAM wParam);
void ShowVisbleBtn(bool value);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BattleCity");
LPCTSTR Btn_Name[16] = { TEXT("block00"),
						 TEXT("block01"),
						 TEXT("block02"),
						 TEXT("block03"),
						 TEXT("block04"),
						 TEXT("block05"),
						 TEXT("block06"),
						 TEXT("block07"),
						 TEXT("block08"),
						 TEXT("block09"),
						 TEXT("block10"),
						 TEXT("block11"),
						 TEXT("block12"),
						 TEXT("block13"),
						 TEXT("block14"),
						 TEXT("erase"),
						};

HWND Btn_Rudio[16];
HDC g_hdc = nullptr;

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	g_hdc = GetDC(hWnd);

	DrawManager::Instance()->Init(g_hdc);
	DrawManager::Instance()->SetCanvasSize(TILEX * 19 + 200, TILEY * 19);
	
	GameManager::Instance()->InIt();

	while (true)
	{
		
		// 메시지큐에 메시지가 있으면 메시지 처리 
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT) break;

				TranslateMessage(&Message);
				DispatchMessage(&Message);
			
		}
		else
		{
			//메세지가 없을때 업데이트를 진행한다.
			MapToolManager::Instance()->Update(g_hdc);
			GameManager::Instance()->Update(g_hdc);

		}
	} //종료직전에 릴리즈 해준다. 


	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	static bool IsLBUTTONDOWN = false;

	switch (iMessage)
	{
		case WM_COMMAND:
		{
			RadioButtonUpdate(wParam);

			switch (LOWORD(wParam))
			{
				case ID_GAMEMENU_NEWGAME:
				{
					ShowVisbleBtn(false);
					MapToolManager::Instance()->SetMapToolStart(false, g_hdc);					
					GameManager::Instance()->Load(hWnd);
					break;
				}
				case ID_GAMEMENU_EXIT:
				{
					break;
				}
				case ID_MAPTOOL_NEWMAP:
				{
					GameManager::Instance()->UnLoad();
					MapToolManager::Instance()->InIt();
					MapToolManager::Instance()->SetMapToolStart(true, g_hdc);
					ShowVisbleBtn(true);
					break;
				}
				case ID_MAPTOOL_LOADMAP:
				{
					GameManager::Instance()->UnLoad();
					MapToolManager::Instance()->Load(hWnd);
					break;
				}
				case ID_MAPTOOL_SAVEMAP:
				{
					MapToolManager::Instance()->Save(hWnd);
					break;
				}
			}

			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			
			return 0;
		}
		case WM_MOUSEMOVE:
		{
			if (IsLBUTTONDOWN)
			{
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);

				MapToolManager::Instance()->TileInfoSet(x, y);
			}
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			MapToolManager::Instance()->TileInfoSet(x, y);

			IsLBUTTONDOWN = true;
			return 0;
		}
		case  WM_LBUTTONUP:
		{
			IsLBUTTONDOWN = false;
			return 0;
		}
		case WM_CREATE:
		{
			CreateRadioButton(hWnd);
			ShowVisbleBtn(false);
			
			return 0;
		}
		case WM_DESTROY:
		{
			MapToolManager::Instance()->Release();
			DrawManager::Instance()->Release();
			PostQuitMessage(0);
			return 0;
		}
	
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));

}

void CreateRadioButton(HWND hWnd)
{
	for (int i = 1; i < 17; i++)
	{
		Btn_Rudio[i - 1] = CreateWindow(TEXT("button"), Btn_Name[i-1], (WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON | WS_GROUP), 900, 20 + 30 * (i - 1), 100, 30, hWnd, (HMENU)i, g_hInst, NULL);
	}
}

void RadioButtonUpdate(WPARAM wParam)
{
	for (int i = 0; i < 16; i++)
	{
		if (i == (wParam - 1))
		{
			SendMessage(Btn_Rudio[i], BM_SETCHECK, BST_CHECKED, 0);
			MapToolManager::Instance()->SetSelectTile(i);
		}
		else
		{
			SendMessage(Btn_Rudio[i], BM_SETCHECK, BST_UNCHECKED, 0);
		}
	}
}

void ShowVisbleBtn(bool value)
{
	if (value)
	{
		for (int i = 0; i < 16; i++)
		{
			ShowWindow(Btn_Rudio[i], SW_SHOW);
		}
	}
	else
	{
		for (int i = 0; i < 16; i++)
		{
			ShowWindow(Btn_Rudio[i], SW_HIDE);
		}
	}
}
