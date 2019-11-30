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
	switch (wMsg)
	{
	// Сообщение при инициализации диалогового окна
	case WM_INITDIALOG:
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