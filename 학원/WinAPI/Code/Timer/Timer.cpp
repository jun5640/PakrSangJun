#include<windows.h>
#include<math.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
void CALLBACK MoveCircleProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Timer"); 

#define PI       3.14159265358979323846

double getRadian(double num)
{
	return num * PI / 180;
}

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

TCHAR sTime[128];
SYSTEMTIME st;
int CircleX = 0;
int CircleY = 200;


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	double r = 500;
	double Hour = 0;
	double min = 0;
	double sec = 0;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, TimerProc);
		SetTimer(hWnd, 2, 100, MoveCircleProc);
		//SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_TIMER:
		
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);


		if (st.wHour >= 12) Hour = 360 / 12  * (st.wHour - 12);
		else Hour = 360 / 12 * st.wHour;

		min = 360 / 60 * st.wMinute;
		sec = 360 / 60 * st.wSecond;

		Ellipse(hdc, 100, 100, 100 + r, 100 + r);
		//중점 350 350
		MoveToEx(hdc, 350, 350, NULL);
		LineTo(hdc, (cosf(getRadian(-90 + Hour)) * 200 + 350), (sinf(getRadian(-90 + Hour))) * 200 + 350);

		MoveToEx(hdc, 350, 350, NULL);
		LineTo(hdc, (cosf(getRadian(-90 + min)) * 230 + 350), (sinf(getRadian(-90 + min))) * 230 + 350);

		MoveToEx(hdc, 350, 350, NULL);
		LineTo(hdc, (cosf(getRadian(-90 + sec)) * 250 + 350), (sinf(getRadian(-90 + sec))) * 250 + 350);

		TextOut(hdc, 100, 100, sTime, lstrlen(sTime));

		Rectangle(hdc, 600, 100, 1100, 600);
		Ellipse(hdc, CircleX, CircleY, CircleX + 100, CircleY + 100);
		

		
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0); 
		return 0; 
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}


void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	
	
	GetLocalTime(&st);
	wsprintf(sTime, TEXT("지금 시간은 %d:%d:%d입니다."),
		st.wHour, st.wMinute, st.wSecond);
	InvalidateRect(hWnd, NULL, TRUE);
}


void CALLBACK MoveCircleProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	static bool MoveTurnX = false;
	static bool MoveTurnY = false;

	if (CircleX <= 600)
	{
		MoveTurnX = !MoveTurnX;
		CircleX = 600;
	}
	else if (CircleX + 100 >= 1100)
	{
		MoveTurnX = !MoveTurnX;
		CircleX = 1000;
	}

	if (CircleY <= 100)
	{
		MoveTurnY = !MoveTurnY;
		CircleY = 100;
	}
	else if (CircleY + 100 >= 600)
	{
		MoveTurnY = !MoveTurnY;
		CircleY = 500;
	}

	if (MoveTurnX) CircleX--;
	else CircleX++;

	if (MoveTurnY) CircleY--;
	else CircleY++;

	InvalidateRect(hWnd, NULL, TRUE);
}