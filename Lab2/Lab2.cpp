#include <windows.h>
#include "resource1.h"
#include <stdlib.h>
#include <stdio.h>

INT             ListIndex; //текущий индекс строки в списке
INT             InstanceIndex; //вспомогательный индекс
HWND    hList1, hCombo1;
//еще один текстовый буфер для передачи данных
char cBuffer[12];

HINSTANCE       ghInstance;   // Переменная для хранения хендела процесса                      
// Описание используемой оконной процедуры
BOOL CALLBACK   PviewDlgProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
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
		char  szListText[256];
		hCombo1 = GetDlgItem(hWnd, IDC_COMBO1);
		ListIndex = SendMessage(hCombo1, CB_ADDSTRING, 0, (DWORD)TEXT(
			"СТРОКА-001"));
		SendMessage(hCombo1, CB_SETITEMDATA, ListIndex, 0);
		// Пример занесения в снисок нескольких строк
		for (InstanceIndex = 1; InstanceIndex < 4; InstanceIndex++)
		{
			sprintf_s(szListText, "СТРОКА-%d", InstanceIndex);
			ListIndex = SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)szListText);
			SendMessage(hCombo1, CB_SETITEMDATA, ListIndex, InstanceIndex);
		}

		SendMessage(hCombo1, WM_SETREDRAW, TRUE, 0);

		SendMessage(hCombo1, CB_SETCURSEL, 0, 0);

		break;
		// Сообщение о закрытии диалогового окна
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
		// Сообщение от элементов диалогового окна
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case  PVIEW_COMPUTER:
		{
			char  szText[256];
			GetDlgItemText(hWnd, IDC_EDIT1, (LPSTR)szText, 255);
			SetWindowText(GetDlgItem(hWnd, IDC_EDIT1), "");
			MessageBox(hWnd, szText, "Принят ТЕКСТ:", MB_OK);

		}
		break;

		default:
			return FALSE;
		}
		break;

	default:
		return FALSE;
	}

	return TRUE;
}