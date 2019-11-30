/*
�������� ���, ����� ��� ������� ���������� ������ Ctrl-����� + Alt-������ + Shift 
� ���� ��������� �������������� �� ���� � ������� ������� �������� � ������-������� ��������
*/
#include <windows.h>
#include "resource.h"

LRESULT CALLBACK PviewDlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(_In_ HINSTANCE   hInstance,
	_In_opt_ HINSTANCE   hPrevInstance,
	_In_ LPSTR       lpCmdLine,
	_In_ int         nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(PVIEW_DLG), 0, PviewDlgProc);
	return 0;
}

//��������� ��������� ��������� ����������� ����
LRESULT CALLBACK PviewDlgProc(HWND hWnd,
	UINT    wMsg,
	WPARAM  wParam,
	LPARAM  lParam)
{
	static size_t dlgCenterWidth, dlgCenterHeight;

	switch (wMsg)
	{
	
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
	{
		if (GetKeyState(VK_LCONTROL) < 0 && GetKeyState(VK_RMENU) < 0 && GetKeyState(VK_SHIFT) < 0)
		{
			HDC hdc = GetDC(hWnd);

			// ��������� ����
			HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
			SelectObject(hdc, pen);

			// ��������� ������ ������
			HBRUSH hbr = CreateSolidBrush(RGB(158, 206, 255));
			HBRUSH hOld = (HBRUSH)SelectObject(hdc, hbr);

			// ����������� ������ ����
			RECT rect;
			GetClientRect(hWnd, &rect);
			LONG dlgCenterWidth = (rect.right - rect.left)/2;
			LONG dlgCenterHeight = (rect.bottom - rect.top)/2;
			
			const size_t RADIUS = 100;

			Ellipse
			(
				hdc,
				dlgCenterWidth - RADIUS,
				dlgCenterHeight + RADIUS/2,
				dlgCenterWidth + RADIUS,
				dlgCenterHeight - RADIUS/2
			);

			// ������� ��������
			SelectObject(hdc, hOld);
			DeleteObject(hbr);
			DeleteObject(pen);
			ReleaseDC(hWnd, hdc);
		}
	}
	break;

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
