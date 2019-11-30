#include <windows.h>
#include "resource.h"

LRESULT CALLBACK PviewDlgProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain
(
	_In_ HINSTANCE hInstance,	// ���������� ���������� ����������. ���� ���������� �������� ����� ������ ���� ��������� � �� �������� ������������. ���������� hInstance ���� ����� ��������� ��������, ���������� � ��������� ���������
	_In_opt_ HINSTANCE,			// ���������� ����������� ���������� ����������. ���� ���������� ������� �� ������ ������ Windows - ������ �����, ��� �� ������� �� ����������. ������ ����� 0
	_In_ LPSTR,					// ��������� �� ������ ��������� ������, ��������� ��� ������� ���������
	_In_ int					// ��� �������� �������� �������� ��� ���� (��������, ��������� ��� �����������)
)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, PviewDlgProc);
	return 0;
}

// ��������� ��������� ��������� ����������� ����
LRESULT CALLBACK PviewDlgProc
(
	HWND    hWnd, 	// ���������� ������������� ���� �� �������� ������ ���������
	UINT    wMsg, 	// ���������, ���������� �� ��
	WPARAM  wParam, // �������������� ���������� ���������
	LPARAM  lParam 	// �������������� ���������� ���������
)
{
	// ���������� ���� ��������� � ���� ������ ���������� ����
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
		// ��������� ����� ��������� ������� � ����, ������� �� ���������� ������� ����� ��������
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

	// ��������� ��� ������������� ����������� ����
	case WM_INITDIALOG:
	{
		// ��������� ������ � ����
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), (LPCSTR)IDI_ICON2);
		SendMessage(hWnd, WM_SETICON, 1, (LPARAM)hIcon);

		// ��������� ������ � ��������� ����
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

		// ��������� �������
		char temp[12] = "";
		GetTimeFormat(0, 0, 0, "hh':'mm':'ss", temp, 8);
		SetDlgItemText(hWnd, IDC_EDIT1, temp);
		// ��������� ������� ��� ���������� ���� �������
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

	// ��������� �� ��������� ����������� ����
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

	// ������� ������ �� ����, ����� ������� ������ ������ � � ���������
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

	// ��������� ������ ���� ��� ��������� ��������� ����	
	case WM_CTLCOLORSTATIC:
	{
		SetBkColor((HDC)wParam, RGB(0xFF, 0xFF, 0xFF));
		return (LRESULT)CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
	}
	break;

	// ��������� ��� �������� ����������� ����
	case WM_CLOSE:
		ShowWindow(hWnd, SW_HIDE);
		break;

	default:
		return FALSE;
	}
	return TRUE;
}