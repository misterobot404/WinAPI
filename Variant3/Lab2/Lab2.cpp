#include <windows.h>
#include "resource1.h"
#include <stdlib.h>
#include <stdio.h>

// Три кнопки, графическое окно, раскрывающийся список.
// В списке два режима : ручной и автомат. При нажатии на первую кнопку – в окне рисуется круг,
// вторую – прямоугольник, третью – линия случайной толщины, цвета и заливки.
// А если включен автомат, то объекты рисуются непрерывно в случайном месте окна.

HWND hCombo1; //	окно листбокс
HWND hWnd; //	главное окно
HANDLE h; //	второй поток

HINSTANCE       ghInstance;   // Переменная для хранения хендела процесса                      
// Описание используемой оконной процедуры
BOOL CALLBACK   PviewDlgProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);

DWORD WINAPI thread2(LPVOID t)
{
	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);
	int RAND;
	//генерируем элементы строки
	while (true)
	{
		RAND = rand() % 3;
		switch (RAND)
		{
		case 0:
		{
			HPEN pen;
			HDC hdc = GetDC(hWnd);

			int x = rand() % 800;
			int y = rand() % 450;
			int z = rand() % 255;
			int width = rand() % 10;		
			pen = CreatePen(PS_SOLID, width, RGB(x, y, z));
			SelectObject(hdc, pen);

			MoveToEx(hdc, x, y, 0);  //перемещение пера
			LineTo(hdc, 600 - y, 230 - x/2); //рисовать линию

			DeleteObject(pen); // удалить  карандаш
			ReleaseDC(hWnd, hdc); // освободить девайс контекста
		}
			break;
		case 1:
		{
			HDC hdc = GetDC(hWnd);	
			double x = rand() % 10 + 1;
			x = x / 10;
			int y = rand() % 300;
			int z = rand() % 5;
			Rectangle(hdc, 260 * x - (y*z), 160 * x - (y*z), 575 * x - (y*z), 300 * x - (y*z));
			ReleaseDC(hWnd, hdc);
		}
			break;
		case 2:
		{
			HDC hdc = GetDC(hWnd);		
			double x = rand() % 10;
			x = x / 5;
			Ellipse(hdc, 300* x, 340 * x, 530 * x, 120* x);
			ReleaseDC(hWnd, hdc);
		}
			break;
		default:
			break;
		}
		Sleep(1000);
	}
	return 0;
}

// Главное приложение программы
int WINAPI    WinMain(HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow)
{
	MSG     msg;

	ghInstance = hInstance;
	// Создание  диалогового окна
	hWnd = CreateDialogParam(hInstance,
		MAKEINTRESOURCE(PVIEW_DLG),
		NULL,
		(DLGPROC)PviewDlgProc,
		(LONG)0);
	// Стандартный цикл обработки сообщений приложения
	while (GetMessage(&msg, NULL, 0, 0))
		if (!IsDialogMessage(hWnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	DestroyWindow(hWnd);
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
	case WM_INITDIALOG:
	{
		hCombo1 = GetDlgItem(hWnd, IDC_COMBO1);

		SendMessage(hCombo1, CB_ADDSTRING, 0, (DWORD)TEXT(
			"Ручной режим"));
		SendMessage(hCombo1, CB_ADDSTRING, 0, (DWORD)TEXT(
			"Автомат"));

		// Выбор эл по умолчанию
		SendMessage(hCombo1, CB_SETCURSEL, 0, 0);
	}
	break;
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
		case  IDC_CIRCLE:
		{
			HDC hdc = GetDC(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			Ellipse(hdc, 300, 340, 530, 120);
			ReleaseDC(hWnd, hdc);
			//	char  szText[256]="hello";
			//	GetDlgItemText(hWnd, IDC_EDIT1, (LPSTR)szText, 255);
			//	SetWindowText(GetDlgItem(hWnd, IDC_EDIT1), "");
			//	MessageBox(hWnd, szText, "Принят ТЕКСТ:", MB_OK);
		}
		break;

		case  IDC_BOX:
		{
			HDC hdc = GetDC(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			Rectangle(hdc, 260, 160, 575, 300);
			ReleaseDC(hWnd, hdc);
		}
		break;

		case  IDC_LINES:
		{
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);

			HPEN pen;
			HDC hdc = GetDC(hWnd);

			int width = rand() % 10;
			int x = rand() % 255;
			int y = rand() % 255;
			int z = rand() % 255;

			pen = CreatePen(PS_SOLID, width, RGB(x, y, z));
			SelectObject(hdc, pen);

			MoveToEx(hdc, 225, 230, 0);  //перемещение пера
			LineTo(hdc, 600, 230); //рисовать линию

			DeleteObject(pen); // удалить  карандаш
			ReleaseDC(hWnd, hdc); // освободить девайс контекста			
		}
		break;
		case IDC_COMBO1:
		{
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				char str[8];
				char str2[] = "Автомат";
				GetDlgItemText(hWnd, IDC_COMBO1, str, 8);
				if (strcmp(str, str2) == 0)
				{
					h = CreateThread(NULL, 0, thread2, NULL, 0, NULL);
				}
				else
				{
					InvalidateRect(hWnd, NULL, TRUE);
					UpdateWindow(hWnd);
					TerminateThread(h, 1);
				}
			}
		}
		break;
		default:
			return FALSE;
		}
	}
	break;

	default:
		return FALSE;
	}
	return TRUE;
}