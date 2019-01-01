#include <Windows.h>
#include <CommCtrl.H>
#include "resource.h"

int position;
HWND hWndDialog;


void SetControlsPosition()
{
	SendDlgItemMessage(hWndDialog, IDC_SPIN1, UDM_SETPOS32, 0, position);
	SendDlgItemMessage(hWndDialog, IDC_SPIN3, UDM_SETPOS32, 0, position);

	SendDlgItemMessage(hWndDialog, IDC_SLIDER1, TBM_SETPOS, TRUE, position);
	SendDlgItemMessage(hWndDialog, IDC_SLIDER2, TBM_SETPOS, TRUE, position);

	SendDlgItemMessage(hWndDialog, IDC_SCROLLBAR1, SBM_SETPOS, position, TRUE);
	SendDlgItemMessage(hWndDialog, IDC_SCROLLBAR2, SBM_SETPOS, position, TRUE);

	SendDlgItemMessage(hWndDialog, IDC_PROGRESS3, PBM_SETPOS, position, 0);
	SendDlgItemMessage(hWndDialog, IDC_PROGRESS2, PBM_SETPOS, position, 0);
}

// Описание используемой оконной процедуры
BOOL CALLBACK   PviewDlgProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
// Главное приложение программы
int WINAPI    WinMain(HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow)
{
	
	MSG     msg;
	HINSTANCE ghInstance = hInstance;
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
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT1), L" Click and drag any Slider or\r\n Scroll Bar control or click on\r\nthe Up-Down control buttons.");
		SetWindowText(hWnd, L"Fun example using - Scroll Bar, Up Down, Progress controls");

		SendDlgItemMessage(hWnd, IDC_SPIN1, UDM_SETRANGE32, 0, 100);		
		SendDlgItemMessage(hWnd, IDC_SPIN3, UDM_SETRANGE32, 0, 100);

		SendDlgItemMessage(hWnd, IDC_SLIDER1, TBM_SETRANGEMIN, FALSE, 0);
		SendDlgItemMessage(hWnd, IDC_SLIDER1, TBM_SETRANGEMAX, FALSE, 100);
		SendDlgItemMessage(hWnd, IDC_SLIDER2, TBM_SETRANGEMIN, FALSE, 0);
		SendDlgItemMessage(hWnd, IDC_SLIDER2, TBM_SETRANGEMAX, FALSE, 100);
		SendDlgItemMessage(hWnd, IDC_SLIDER2, TBM_SETTICFREQ, 1, 0);

		SendDlgItemMessage(hWnd, IDC_SCROLLBAR1, SBM_SETRANGE, 0, 100);
		SendDlgItemMessage(hWnd, IDC_SCROLLBAR2, SBM_SETRANGE, 0, 100);

		SendDlgItemMessage(hWnd, IDC_PROGRESS3, PBM_SETRANGE32, 0, 100);
		SendDlgItemMessage(hWnd, IDC_PROGRESS2, PBM_SETRANGE32, 0, 100);
		SetFocus(hWnd);

	}
	break;

	// Горизонтальное изменение эллемента	
	case WM_HSCROLL:
	{
		position = SendDlgItemMessage(hWnd, IDC_SPIN1, UDM_GETPOS32, 0, 0);
		SetControlsPosition();

		switch (LOWORD(wParam))
		{		
		// Нажата клавиша стрелка влево
		case SB_LINEUP:
			position -= 1;
			SetControlsPosition();
			break;
		// Нажата клавиша стрелка вправо 
		case SB_LINEDOWN:
			position += 1;
			SetControlsPosition();
			break;
		// Пользователь отпустил кнопку мыши после перемещения ползунка
		case SB_THUMBPOSITION:
			position = SendDlgItemMessage(hWnd, IDC_SCROLLBAR2, SBM_GETPOS, 0, 0);
			SetControlsPosition();
			break;
		// Ползунок перемещается с помощью мыши
		case SB_THUMBTRACK:
			position = HIWORD(wParam);
			SetControlsPosition();
			break;
		}
	}
	break;

	// Вертикальное изменение эллемента
	case WM_VSCROLL:
	{
		position = SendDlgItemMessage(hWnd, IDC_SPIN3, UDM_GETPOS32, 0, 0);
		SetControlsPosition();

		switch (LOWORD(wParam))
		{
		// Нажата клавиша стрелка влево
		case SB_LINEUP:
			position -= 1;
			SetControlsPosition();
			break;
		// Нажата клавиша стрелка вправо 
		case SB_LINEDOWN:
			position += 1;
			SetControlsPosition();
			break;
		// Пользователь отпустил кнопку мыши после перемещения ползунка
		case SB_THUMBPOSITION:
			position = SendDlgItemMessage(hWnd, IDC_SCROLLBAR2, SBM_GETPOS, 0, 0);
			SetControlsPosition();
			break;
		// Ползунок перемещается с помощью мыши
		case SB_THUMBTRACK:
			position = HIWORD(wParam);
			SetControlsPosition();
			break;
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
