#include <windows.h>
#include "resource.h"

HINSTANCE       ghInstance;   // Переменная для хранения хендела процесса                      
// Описание используемой оконной процедуры
BOOL CALLBACK   PviewDlgProc(HWND  hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
// Главное приложение программы
int WINAPI    WinMain(HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow)
{
	HWND hWndDialog;
	MSG     msg;

	ghInstance = hInstance;
	// Создание  диалогового окна
	hWndDialog = CreateDialogParam(hInstance,
		MAKEINTRESOURCE(PVIEW_DLG),
		NULL,
		(DLGPROC)PviewDlgProc,
		(LONG)0);
	// Стандартный цикл обработки сообщений приложения
	while (GetMessage(&msg, NULL, 0, 0))
		if (!IsDialogMessage(hWndDialog, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	DestroyWindow(hWndDialog);
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
		switch (LOWORD(wParam))
		{

		default:
			return FALSE;
		}
		break;

	default:
		return FALSE;
	}

	return TRUE;
}