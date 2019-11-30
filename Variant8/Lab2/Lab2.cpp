/*
Меню (двухуровневое), выбирает вид фигуры, кнопка – рисует эту фигуру на графическом окне.
Другая кнопка – стирает эту фигуру. Спиннер выбирает толщину линии.
*/

#include <windows.h>
#include "resource.h"
#include <string>
#include <CommCtrl.H>

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
	switch (wMsg)
	{
	case WM_INITDIALOG:
	{
		// Устанавливаем стандартные значения
		SendDlgItemMessage(hWnd, IDC_SPIN2, UDM_SETRANGE32, 1, 50);
		CheckRadioButton(hWnd, IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);
		SendDlgItemMessage(hWnd, IDC_SPIN2, UDM_SETPOS32, 0, 1);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT1), "1");
	}
	break;

	// Сообщение при закрытии диалогового окна
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

		// Сообщение от элементов диалогового окна
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case  ID_BUTTON_CIRCLE:
		{
			CheckRadioButton(hWnd, IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);
		}
		break;

		case  ID_BUTTON_RECTANGLE:
		{
			CheckRadioButton(hWnd, IDC_RADIO1, IDC_RADIO3, IDC_RADIO2);
		}
		break;

		case  ID_BUTTON_ELLIPSE:
		{
			CheckRadioButton(hWnd, IDC_RADIO1, IDC_RADIO3, IDC_RADIO3);
		}
		break;
		case  IDOK:
		{
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);

			HDC hdc = GetDC(hWnd);

			// Установка пера
			int widthPen = SendDlgItemMessage(hWnd, IDC_SPIN2, UDM_GETPOS32, 0, 0);
			HPEN pen = CreatePen(PS_SOLID, widthPen, RGB(0, 255, 0));
			SelectObject(hdc, pen);

			// Определение центра окна
			RECT rect;
			GetClientRect(hWnd, &rect);
			LONG dlgCenterWidth = (rect.right - (float)rect.left) /1.9;
			LONG dlgCenterHeight = (rect.bottom - (float)rect.top) / 1.4;

			const size_t RADIUS = 100;

			if (IsDlgButtonChecked(hWnd, IDC_RADIO1))
			{
				Ellipse
				(
					hdc,
					dlgCenterWidth - RADIUS,
					dlgCenterHeight + RADIUS,
					dlgCenterWidth + RADIUS,
					dlgCenterHeight - RADIUS
				);
			}
			else if (IsDlgButtonChecked(hWnd, IDC_RADIO2))
			{
				Rectangle
				(
					hdc,
					dlgCenterWidth - RADIUS,
					dlgCenterHeight + RADIUS / 2,
					dlgCenterWidth + RADIUS,
					dlgCenterHeight - RADIUS / 2
				);
			}
			else if (IsDlgButtonChecked(hWnd, IDC_RADIO3))
			{
				Ellipse
				(
					hdc,
					dlgCenterWidth - RADIUS,
					dlgCenterHeight + RADIUS / 2,
					dlgCenterWidth + RADIUS,
					dlgCenterHeight - RADIUS / 2
				);
			}

			// Очистка ресурсов
			DeleteObject(pen);
			ReleaseDC(hWnd, hdc);
		}
		break;

		case  IDCANCEL:
		{
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;

		default:
			return FALSE;
		}
		break;
	}

	// Вертикальное изменение спина
	case WM_VSCROLL:
	{
		// Меняем поле информирующее пользователя о ширине линии кисти
		int widthPen = SendDlgItemMessage(hWnd, IDC_SPIN2, UDM_GETPOS32, 0, 0);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT1), std::to_string(widthPen).c_str());
	}
	default:
		return FALSE;
	}
	return TRUE;
}
