#include <windows.h>
#include "resource.h"

HINSTANCE       ghInstance;   // ���������� ��� �������� ������� ��������                      
// �������� ������������ ������� ���������
BOOL CALLBACK   PviewDlgProc(HWND  hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
// ������� ���������� ���������
int WINAPI    WinMain(HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow)
{
	HWND hWndDialog;
	MSG     msg;

	ghInstance = hInstance;
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
		break;
		// ��������� � �������� ����������� ����
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
		// ��������� �� ��������� ����������� ����
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		default:
			return FALSE;
		}
		break;

	default:
		return FALSE;
	}

	return TRUE;
}