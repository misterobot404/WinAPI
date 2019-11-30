#include <windows.h>
#include "resource.h"

LRESULT CALLBACK PviewDlgProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain
(
	_In_ HINSTANCE hInstance,	// дескриптор экземпляра приложения. Этот дескриптор содержит адрес начала кода программы в ее адресном пространстве. Дескриптор hInstance чаще всего требуется функциям, работающим с ресурсами программы
	_In_opt_ HINSTANCE,			// дескриптор предыдущего экземпляра приложения. Этот дескриптор остался от старых версий Windows - скорее всего, вам он никогда не пригодится. Всегда равен 0
	_In_ LPSTR,					// указатель на начало командной строки, введенной при запуске программы
	_In_ int					// это значение содержит желаемый вид окна (например, свернутый или развернутый)
)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, PviewDlgProc);
	return 0;
}

// Процедура обработки сообщений диалогового окна
LRESULT CALLBACK PviewDlgProc
(
	HWND    hWnd, 	// уникальный идентификатор окна от которого пришло сообщение
	UINT    wMsg, 	// сообщение, получаемое от ОС
	WPARAM  wParam, // дополнительная информация сообщения
	LPARAM  lParam 	// дополнительная информация сообщения
)
{
	// Добавление двух категорий в меню иконки системного трея
	if (lParam == WM_RBUTTONDOWN)
	{
		SetForegroundWindow(hWnd);
		POINT mouse;
		GetCursorPos(&mouse);
		HMENU hMenu = CreatePopupMenu();
		AppendMenu(hMenu, MF_ENABLED, SHOW, "Show Calendar");
		AppendMenu(hMenu, MF_SEPARATOR, 1000, "");
		AppendMenu(hMenu, MF_ENABLED, EXIT, "Exit Program");
		TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, mouse.x, mouse.y, 0, hWnd, NULL);
	}

	switch (wMsg)
	{
	case WM_PAINT:
	{
		// Отрисовка белой центровой области в окно, которую не получилось сделать через свойства
		RECT rect;
		rect.bottom = 422;
		rect.top = 12;
		rect.left = 13;
		rect.right = 604;
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		FillRect(ps.hdc, &rect, (HBRUSH)GetStockObject(COLOR_WINDOW + 1));
		EndPaint(hWnd, &ps);
	}
	break;

	// Сообщение при инициализации диалогового окна
	case WM_INITDIALOG:
	{
		// Установка иконки у окна
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), (LPCSTR)IDI_ICON2);
		SendMessage(hWnd, WM_SETICON, 1, (LPARAM)hIcon);

		// Установка иконки в системном трее
		NOTIFYICONDATA nid;
		memset(&nid, 0, sizeof(NOTIFYICONDATA));
		nid.cbSize = sizeof(NOTIFYICONDATA);
		nid.hWnd = hWnd;
		nid.uID = 1;
		nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		nid.uCallbackMessage = WM_USER + 200;
		nid.hIcon = LoadIcon(GetModuleHandle(NULL), (LPCSTR)IDI_ICON2);
		lstrcpy(nid.szTip, "Popup Calendar");
		Shell_NotifyIcon(NIM_ADD, &nid);

		// Установка времени
		char temp[12] = "";
		GetTimeFormat(0, 0, 0, "hh':'mm':'ss", temp, 8);
		SetDlgItemText(hWnd, IDC_EDIT1, temp);
		// Установка таймера для обновления поля времени
		SetTimer(hWnd, 1, 1000, 0);
	}
	break;

	case WM_TIMER:
	{
		char temp[12] = "";
		GetTimeFormat(0, 0, 0, "hh':'mm':'ss", temp, 8);
		SetDlgItemText(hWnd, IDC_EDIT1, temp);
	}
	break;	

	// Сообщение от элементов диалогового окна
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case SHOW:
			ShowWindow(hWnd, SW_SHOW);
			break;

		case EXIT:
			PostQuitMessage(0);

		default:
			return FALSE;
		}
		break;
	}

	// Удаляем иконку из трея, иначе сборщик мусора удалит её с задержкой
	case WM_DESTROY:
	{
		NOTIFYICONDATA nid;
		memset(&nid, 0, sizeof(NOTIFYICONDATA));
		nid.cbSize = sizeof(NOTIFYICONDATA);
		nid.hWnd = hWnd;
		nid.uID = 1;
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}
	break;

	// Установка белого фона для остальных элементов окна	
	case WM_CTLCOLORSTATIC:
	{
		SetBkColor((HDC)wParam, RGB(0xFF, 0xFF, 0xFF));
		return (LRESULT)CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
	}
	break;

	// Сообщение при закрытии диалогового окна
	case WM_CLOSE:
		ShowWindow(hWnd, SW_HIDE);
		break;

	default:
		return FALSE;
	}
	return TRUE;
}