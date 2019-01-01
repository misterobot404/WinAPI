#include <Windows.h>

#define PNT 12
#define PNT2 1

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#define WMAIN_CLASSNAME     L"WndClassTestMyName"
#define WMAIN_CAPTION       L"WndCaption"

HWND hWnd; //	главное окно
HANDLE h; //	второй поток

DWORD WINAPI threadCircle(LPVOID t)
{
	HBRUSH br;
	while (true)
	{
		HDC hdc = GetDC(hWnd);
		double x = rand() % 9;

		br = CreateSolidBrush(RGB(123, 23, 72));
		SelectObject(hdc, br);

		Ellipse(hdc, 300 * x / PNT, 340 * x / PNT, 530 * x / PNT, 120 * x / PNT);
		ReleaseDC(hWnd, hdc);
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI threadBox(LPVOID t)
{
	HBRUSH br;
	while (true)
	{
		HDC hdc = GetDC(hWnd);
		br = CreateSolidBrush(RGB(00, 23, 72));
		SelectObject(hdc, br);

		double x = rand() % 10;
		x = x / 10;
		int y = rand() % 300;
		int z = rand() % 5;
		Rectangle(hdc, (260 * x - (y*z)) / PNT2, (160 * x - (y*z)) / PNT2, (575 * x - (y*z)) / PNT2, (300 * x - (y*z)) / PNT2);
		ReleaseDC(hWnd, hdc);
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI threadTriangle(LPVOID t)
{
	while (true)
	{
		POINT ptArray1[3];
		HRGN Rgn3, Rgn4;
		HBRUSH hBrush3;
		LOGBRUSH lb;

		HDC hDC = GetDC(hWnd);
	
		double x = rand() % 5;

		ptArray1[0].x = 150 /x; ptArray1[0].y = 250 / x;
		ptArray1[1].x = 150 / x; ptArray1[1].y = 150 / x;
		ptArray1[2].x = 250 / x; ptArray1[2].y = 250 / x;
		Rgn3 = CreatePolygonRgn(ptArray1, sizeof(ptArray1) / sizeof(POINT), ALTERNATE);
			
		lb.lbStyle = BS_HATCHED;
		lb.lbColor = RGB(0, 255, 0);
		lb.lbHatch = HS_DIAGCROSS;
		hBrush3 = CreateSolidBrush(RGB(0, 0, 255));
		FillRgn(hDC, Rgn3, hBrush3);

		Sleep(1000);
		ReleaseDC(hWnd, hDC);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hThisInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszArgument,
	int nCmdShow)
{	
	MSG msg;
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hInstance = hPrevInstance;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = WMAIN_CLASSNAME;
	wc.lpszMenuName = NULL;

	if (!RegisterClass(&wc))
		return 0;

	hWnd = CreateWindow(WMAIN_CLASSNAME, WMAIN_CAPTION, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 500, 300, HWND_DESKTOP, NULL, hPrevInstance, 0);

	if (!hWnd)
		return 0;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{

	case WM_CREATE:
	{
		h = CreateThread(NULL, 0, threadCircle, NULL, 0, NULL);
		h = CreateThread(NULL, 0, threadBox, NULL, 0, NULL);
		h = CreateThread(NULL, 0, threadTriangle, NULL, 0, NULL);
	}
	break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}