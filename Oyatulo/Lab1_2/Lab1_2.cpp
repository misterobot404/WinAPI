/*
Сделайте так, чтобы при каждом повторном запуске Вашего приложения случайным образом задавался цвет шрифта в окне.
*/
#include <windows.h>
#include "resource.h"
#include <ctime>

BOOL CALLBACK   PviewDlgProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);

int WINAPI    WinMain(HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(PVIEW_DLG), 0, PviewDlgProc);
	return 0;
}

//Процедура обработки сообщений диалогового окна
BOOL CALLBACK   PviewDlgProc(HWND    hWnd,
	UINT    wMsg,
	WPARAM  wParam,
	LPARAM  lParam)
{
	switch (wMsg)
	{
		// Сообщение о инициализации диалогового окна
	case WM_INITDIALOG:
		break;

		// Сообщение о закрытии диалогового окна
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

		// Сообщение от элементов диалогового окна
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		default:
			return FALSE;
		}
		break;
	}

	case WM_CTLCOLORSTATIC:
	{
		if ((HWND)lParam == GetDlgItem(hWnd, ID_COLOR))
		{
			srand(time(0));
			int R = rand() % 255;
			int G = rand() % 255;
			int B = rand() % 255;

			HDC hdc = (HDC)wParam;
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(R, G, B));
			return (int)GetStockObject(NULL_BRUSH);
		}
	}
	break;

	default:
		return FALSE;
	}

	return TRUE;
}
