#include <windows.h>
#include "resource.h"


// �������� ������������ ������� ���������
BOOL CALLBACK   PviewDlgProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
// ������� ���������� ���������
int WINAPI    WinMain(HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow)
{
	HWND hWndDialog;
	MSG     msg;

	HINSTANCE ghInstance = hInstance;
	// ��������  ����������� ����
	hWndDialog = CreateDialogParam(hInstance,
		MAKEINTRESOURCE(PVIEW_DLG),
		NULL,
		(DLGPROC)PviewDlgProc,
		(LONG)0);
	
	// ����������� ���� ��������� ��������� ����������
	while (GetMessage(&msg, NULL, 0, 0))
		if (!IsDialogMessage(hWndDialog, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	DestroyWindow(hWndDialog);
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
	{
		HWND editText = GetDlgItem(hWnd, IDC_EDIT1);
		SetWindowText(editText, L" Click and drag any Slider or\r\n Scroll Bar control or click on\r\nthe Up-Down control buttons.");
		//SetFocus(hWnd);
		SetWindowText(hWnd, L"Fun example using - Scroll Bar, Up Down, Progress controls");
	}
	break;

	// ��������� � �������� ����������� ����
	case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
	break;

	// ��������� �� ��������� ����������� ����
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