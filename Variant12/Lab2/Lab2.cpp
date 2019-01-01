/*
������� ����������� ������ �� ���������� Win API,
���������� ��� ������, ��� ������ � ������,
���� (�������������), �������������� ������.
*/

#include <windows.h>
#include "resource.h"

BOOL CALLBACK   PviewDlgProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
void clearField(HWND hWnd);

int WINAPI    WinMain(HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, PviewDlgProc);
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
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (DWORD)TEXT(
			"> 1 ����"));
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (DWORD)TEXT(
			"< 1 ����"));

		// ����� �� �� ���������
		SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_SETCURSEL, 0, 0);
	}
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
		case  ID_EXIT1:
			PostMessage(hWnd, WM_QUIT, 0, 0);
			break;

		case  ID_EXIT2:
			PostMessage(hWnd, WM_QUIT, 0, 0);
			break;

		case  ID_EXIT3:
			PostMessage(hWnd, WM_QUIT, 0, 0);
			break;

		case  IDOK:
			MessageBox(hWnd, "��������� ��������", "1C: �����������", MB_ICONINFORMATION);
			clearField(hWnd);
			break;

		case  IDC_BUTTON1:
			clearField(hWnd);
			break;
			
		case  IDCANCEL:
			PostMessage(hWnd, WM_QUIT, 0, 0);
			break;

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

void clearField(HWND hWnd)
{
	SetWindowText(GetDlgItem(hWnd, IDC_EDIT1), "");
	SendMessage(GetDlgItem(hWnd, IDC_RADIO1), BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(GetDlgItem(hWnd, IDC_RADIO2), BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(GetDlgItem(hWnd, IDC_RADIO3), BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(GetDlgItem(hWnd, IDC_CHECK1), BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(GetDlgItem(hWnd, IDC_CHECK2), BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(GetDlgItem(hWnd, IDC_CHECK3), BM_SETCHECK, BST_UNCHECKED, 0);
}