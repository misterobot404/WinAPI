#include <windows.h>
#include "resource.h"

BOOL CALLBACK   PviewDlgProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);

int WINAPI    WinMain(HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, PviewDlgProc);
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

	default:
		return FALSE;
	}

	return TRUE;
}
