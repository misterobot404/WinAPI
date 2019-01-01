#include <windows.h>
#include <conio.h>
#include "resource.h"
#include <string>

//	Раскрывающийся список, окно деревьев. 
//	В списке выбирается дисковод. 
//	В окне деревьев отображается его файловое содержание.

HINSTANCE       ghInstance;   // Переменная для хранения хендела процесса    
wchar_t buf[5];
//HDC hdc;
//PAINTSTRUCT ps;
HWND hCombo1; //	окно листбокс
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
	{
		hCombo1 = GetDlgItem(hWnd, IDC_COMBO1);

		TCHAR szBuffer[1024];
		DWORD drives = GetLogicalDriveStrings(1024, szBuffer);
		TCHAR *pch = szBuffer;

		while (*pch) {
			SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)pch);
			pch += 4;
		}
	}
	break;

	// Сообщение о закрытии диалогового окна
	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	// Сообщение от элементов диалогового окна
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_COMBO1:
		{
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				//	Clear old combobox
				SendDlgItemMessage(hWnd, IDC_COMBO2, CB_RESETCONTENT, 0, 0);

				GetDlgItemTextW(hWnd, IDC_COMBO1, buf, 30);

				//	hCombo1 = GetDlgItem(hWnd, IDC_COMBO1);
				//	GetWindowTextW(hCombo1, buf, sizeof(buf));
				//	MessageBoxW(hWnd, buf, L"", NULL); 

				hCombo1 = GetDlgItem(hWnd, IDC_COMBO2);

				WIN32_FIND_DATAW wfd;

				buf[2] = L'\\';
				buf[3] = L'\*';
				HANDLE const hFind = FindFirstFileW(buf, &wfd);
				if (INVALID_HANDLE_VALUE != hFind)
				{
					do
					{
						SendMessageW(hCombo1, CB_ADDSTRING, NULL, (LPARAM)&wfd.cFileName);
					} while (NULL != FindNextFileW(hFind, &wfd));
					FindClose(hFind);
					InvalidateRect(hCombo1, NULL, TRUE);
					UpdateWindow(hCombo1);
				}
			}
		}
		break;

		/*case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			ps.fErase = true;
			char szText[13] = "Hello World!";
			TextOut(hdc, 100, 100, szText, 12);
			EndPaint(hWnd, &ps);
		}
		break;*/

		default:
			return FALSE;
		}
	}
	break;

	/*case WM_LBUTTONDOWN:
	{
		char szText[13] = "Hello World!";
		TextOut(hdc, 100, 100, szText, 12);
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
	}
	break;*/

	default:
		return FALSE;
	}
	return TRUE;
}
