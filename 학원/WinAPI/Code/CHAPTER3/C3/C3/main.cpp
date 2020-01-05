#include<windows.h>
#include<vector>

using namespace std;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Input_Mouse");

class CustomPoint
{
public:
	int x;
	int y;
	int r;
	bool isRect = false;
	CustomPoint(int x, int y, int r, int isRect)
	{
		this->x = x;
		this->y = y;
		this->r = r;
		this->isRect = isRect;

	}
};

vector<CustomPoint> vCP;


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


	CustomPoint CP1 = CustomPoint(100, 500, 100, false);
	CustomPoint CP2 = CustomPoint(200, 500, 100, false);
	CustomPoint CP3 = CustomPoint(300, 500, 100, false);

	CustomPoint CP4 = CustomPoint(100, 600, 100, true);
	CustomPoint CP5 = CustomPoint(200, 600, 100, true);
	CustomPoint CP6 = CustomPoint(300, 600, 100, true);

	vCP.push_back(CP1);
	vCP.push_back(CP2);
	vCP.push_back(CP3);
	vCP.push_back(CP4);
	vCP.push_back(CP5);
	vCP.push_back(CP6);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

int moveX = 100;
int moveY = 100;

int x = 0;
int y = 0;

int RectStartX = 100;
int RectEndX = 500;
int RectStartY = 100;
int RectEndY = 500;







LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	
	HDC hdc;
	PAINTSTRUCT ps;

	int r = 50;
	vector<CustomPoint>::iterator iter = vCP.begin();

	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_LEFT:
			moveX -= 10;
			break;
		case VK_RIGHT:
			moveX += 10;
			break;
		case VK_UP:
			moveY -= 10;
			break;
		case VK_DOWN:
			moveY += 10;
			break;
		}

		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_RBUTTONDOWN:
		if (MessageBox(hWnd, TEXT("마우스 우클릭"), TEXT("MessageBox"), MB_OK) == IDOK)
		{
			vector<CustomPoint>::iterator iter = vCP.begin();
			for (iter; iter != vCP.end(); iter++)
			{
				iter->isRect = !iter->isRect;
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		Rectangle(hdc, RectStartX, RectStartY, RectEndX, RectEndY);

		if (x - r < RectStartX) x = RectStartX + r;
		if (x + r > RectEndX) x = RectEndX - r;
		if (y - r < RectStartY) y = RectStartY + r;
		if (y + r > RectEndY) y = RectEndY - r;
		//
		// 마우스 따라다니는 아이
		//
		Ellipse(hdc, x - r, y - r, x + r, y + r);

		//
		//
		//
		
		for (iter; iter != vCP.end(); iter++)
		{
			if (iter->isRect)
			{
				Rectangle(hdc, iter->x, iter->y, iter->x + iter->r, iter->y + iter->r);
			}
			else
			{
				Ellipse(hdc, iter->x, iter->y, iter->x + iter->r, iter->y + iter->r);
			}
		}

		//
		// 키보드로 움직이는 아이
		//
		Ellipse(hdc, moveX - r / 2, moveY - r / 2, moveX + r / 2, moveY + r / 2);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}