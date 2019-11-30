/*
���� (�������������), �������� ��� ������, ������ � ������ ��� ������ �� ����������� ����.
������ ������ � ������� ��� ������. ������� �������� ������� �����.
*/

#include <windows.h>
#include "resource.h"
#include <string>
#include <CommCtrl.H>

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
	switch (wMsg)
	{
	case WM_INITDIALOG:
	{
		// ������������� ����������� ��������
		SendDlgItemMessage(hWnd, IDC_SPIN2, UDM_SETRANGE32, 1, 50);
		CheckRadioButton(hWnd, IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);
		SendDlgItemMessage(hWnd, IDC_SPIN2, UDM_SETPOS32, 0, 1);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT1), "1");
	}
	break;

	// ��������� ��� �������� ����������� ����
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

		// ��������� �� ��������� ����������� ����
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

			// ��������� ����
			int widthPen = SendDlgItemMessage(hWnd, IDC_SPIN2, UDM_GETPOS32, 0, 0);
			HPEN pen = CreatePen(PS_SOLID, widthPen, RGB(0, 255, 0));
			SelectObject(hdc, pen);

			// ����������� ������ ����
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

			// ������� ��������
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

	// ������������ ��������� �����
	case WM_VSCROLL:
	{
		// ������ ���� ������������� ������������ � ������ ����� �����
		int widthPen = SendDlgItemMessage(hWnd, IDC_SPIN2, UDM_GETPOS32, 0, 0);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT1), std::to_string(widthPen).c_str());
	}
	default:
		return FALSE;
	}
	return TRUE;
}
