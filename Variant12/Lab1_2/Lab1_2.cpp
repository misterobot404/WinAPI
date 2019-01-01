/*
�������� ���, ����� ��� ������ ��������� ������� ������ ���������� ��������� ������� ��������� ���� ������ � ����.
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

//��������� ��������� ��������� ����������� ����
BOOL CALLBACK   PviewDlgProc(HWND    hWnd,
	UINT    wMsg,
	WPARAM  wParam,
	LPARAM  lParam)
{
	switch (wMsg)
	{
		// ��������� � ������������� ����������� ����
	case WM_INITDIALOG:
		break;

		// ��������� � �������� ����������� ����
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

		// ��������� �� ��������� ����������� ����
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
