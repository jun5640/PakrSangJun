#include<windows.h>
#include<math.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TextOut"); 

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
	int r = 100; //반지름

	/*RECT rt = { 100, 100, 400, 300 };
	LPCSTR str = TEXT("So keep your eyes on me now"
		"무엇을 보든 좋아할 거야 닿을 수 없는 Level"
		"나와 대결 원한 널 확신해");*/

	double Rage = 100; //합

	double dotX1 = 20;
	double dotY1 = 0;

	double dotX2 = -20;
	double dotY2 = 0;
	switch (iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//SetTextAlign(hdc, TA_CENTER);
		TextOut(hdc, 100, 100, TEXT("Beautiful Korea"), 15);
		//DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);

	/*	for(int i = 0; i < 100; i++)
			SetPixel(hdc, 10 + (i * 3), 10, RGB(255, 0, 0));*/

		

		// sin0 = r / y y=알수 없다. x = r cos0 , y = r sin0
		// 타원은 임의의 한 점과 가지고 있는 두점 사이의 거리의 합이 일정수인 점들의 집합이다.

		for (int i = 0; i < 360; i++)
		{
			for (double j = -60; j <= 60; j += 0.01)
			{
				double x = cos(i) * j;
				double y = sin(i) * j;

				int dist1 = (dotX1 - x) * (dotX1 - x) + (dotY1 - y) * (dotY1 - y);
				int dist2 = (dotX2 - x) * (dotX2 - x) + (dotY2 - y) * (dotY2 - y);

				dist1 = sqrt(dist1);
				dist2 = sqrt(dist2);

				if (dist1 + dist2 == Rage)
				{
					SetPixel(hdc, x + 300, y + 300, RGB(0, 255, 0));
				}
			}
		}

		for (int i = 0; i < 360; i++)
		{
			int x = r * cos(i);
			int y = r * sin(i);

			SetPixel(hdc, x + 200, y + 200, RGB(255, 0, 0));
		}

		/*MoveToEx(hdc, 50, 50, NULL);
		LineTo(hdc, 300, 90);
		Rectangle(hdc, 50, 100, 200, 180);
		Ellipse(hdc, 220, 100, 400, 200);
		EndPaint(hWnd, &ps);
*/
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);

		TextOut(hdc, 100, 100, TEXT("Beautiful Korea"), 15);

		ReleaseDC(hWnd, hdc);
		return 0; 
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
