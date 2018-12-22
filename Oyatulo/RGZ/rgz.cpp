#include <windows.h>
#include <string>
#include "resource.h"
using namespace std;
BOOL CALLBACK   PviewDlgProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);

int WINAPI    WinMain(HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, PviewDlgProc);
	return 0;
}

//Процедура обработки сообщений диалогового окна
BOOL CALLBACK   PviewDlgProc(HWND    hWnd,
	UINT    wMsg,
	WPARAM  wParam,
	LPARAM  lParam)
{
	switch (wMsg)
	{
	// Сообщение о инициализации диалогового окна
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(NULL, IDI_ASTERISK);
		SendMessage(hWnd, WM_SETICON, 1, (LPARAM)hIcon);

		HWND  hwndList = GetDlgItem(hWnd, IDC_LIST1);

		wchar_t buf[MAX_PATH];
		GetCurrentDirectoryW(sizeof(buf), buf);

		wstring str = buf;
		str +=  L'\\';
		str += L'\*';
		WIN32_FIND_DATAW wfd;
		HANDLE const hFind = FindFirstFileW(str.c_str(), &wfd);
		if (INVALID_HANDLE_VALUE != hFind)
		{
			do
			{
				wchar_t *txt = wfd.cFileName;
				wstring ws(txt);
				string strw(ws.begin(), ws.end());			
				strw = strw.substr(strw.find_last_of(".") + 1);

				if (strw == "jpg" || strw == "png" || strw == "bmp") {
					SendMessageW(hwndList, LB_ADDSTRING, NULL, (LPARAM)&wfd.cFileName);
				}	
			} while (NULL != FindNextFileW(hFind, &wfd));
			FindClose(hFind);
		}
		
	}
	break;

	// Сообщение о закрытии диалогового окна
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	// Сообщение от элементов диалогового окна
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDCLOSE:
			PostMessage(hWnd, WM_QUIT, 0, 0);
			break;

		case IDC_LIST1:
		{
			if (HIWORD(wParam) == CBN_DBLCLK)
			{
				int number = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETCURSEL, 0, wParam);
				wchar_t  name[MAX_PATH];
				SendMessageW(GetDlgItem(hWnd, IDC_LIST1), LB_GETTEXT, (WPARAM)number, (LPARAM)name);

				wchar_t buf[MAX_PATH];
				GetCurrentDirectoryW(sizeof(buf), (LPWSTR)buf);

				wstring str = (LPWSTR)buf;
				str += L'\\';
				str += (LPWSTR)name;

				SystemParametersInfoW(SPI_SETDESKWALLPAPER, NULL, (PVOID)(str.c_str()), SPIF_UPDATEINIFILE);
			}
		}
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
