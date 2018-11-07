#include <tchar.h>
#include <windows.h>
#include <process.h>
#include "resource.h"

// Идентификаторы кнопок
#define EXIT 404
#define RUN 405

HINSTANCE hInst;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK HideDialogProc(HWND, UINT, WPARAM, LPARAM);


/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain(HINSTANCE hThisInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszArgument,
	int nCmdShow)
{
	HWND hwnd;               /* This is the handle for our window */
	MSG messages;            /* Here messages to the application are saved */
	WNDCLASSEX wincl;        /* Data structure for the windowclass */
	hInst = hThisInstance;

	/* The Window structure */
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
	wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
	wincl.cbSize = sizeof(WNDCLASSEX);

	/* Use default icon and mouse-pointer */
	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;                 /* No menu */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */
	/* Use Windows's default colour as the background of the window */
	wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

	/* Register the window class, and if it fails quit the program */
	if (!RegisterClassEx(&wincl))
		return 0;

	/* The class is registered, let's create the program*/
	hwnd = CreateWindowEx(
		0,                   /* Extended possibilites for variation */
		szClassName,         /* Classname */
		_T("Code::Blocks Template Windows App"),       /* Title Text */
		WS_OVERLAPPEDWINDOW, /* default window */
		CW_USEDEFAULT,       /* Windows decides the position */
		CW_USEDEFAULT,       /* where the window ends up on the screen */
		544,                 /* The programs width */
		375,                 /* and height in pixels */
		HWND_DESKTOP,        /* The window is a child-window to desktop */
		NULL,                /* No menu */
		hThisInstance,       /* Program Instance handler */
		NULL                 /* No Window Creation data */
	);

	while (GetMessage(&messages, NULL, 0, 0))
	{
		/* Translate virtual-key messages into character messages */
		TranslateMessage(&messages);
		/* Send message to WindowProcedure */
		DispatchMessage(&messages);
	}

	return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure(HWND hWnd,		// дескриптор окошка
	UINT message,	// сообщение, посылаемое ОС
	WPARAM wParam, // параметры
	LPARAM lParam)	// сообщений, для последующего обращения
{
	if (lParam == WM_RBUTTONDOWN)
	{
		SetForegroundWindow(hWnd);
		POINT mouse;
		GetCursorPos(&mouse);
		HMENU hMenu = CreatePopupMenu();
		AppendMenu(hMenu, MF_ENABLED, RUN, L"Hide Desktop");
		AppendMenu(hMenu, MF_ENABLED, EXIT, L"Exit Program");
		TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, mouse.x, mouse.y, 0, hWnd, NULL);
	}

	switch (message)
	{
		// Сообщение WM_COMMAND посылается когда:
		// - производится выбор пункта меню
		// - элемент управления посылает уведомительное сообщение родительскому окну
		// - происходит нажатие клавиши акселератора.
	case WM_COMMAND:
	{
		// Wparam - определяет источник сообщения: элемент управления или акселератор.
		// Lparam - идентификатор элемента, если это не акселератор.
		switch (LOWORD(wParam))
		{
		case RUN:
		{
			CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)HideDialogProc, 0);
		}
		break;

		case EXIT:
		{
			exit(1);
		}
		break;
		}
	}
	break;

	case WM_CREATE:
	{
		NOTIFYICONDATA nid;
		memset(&nid, 0, sizeof(NOTIFYICONDATA));
		nid.cbSize = sizeof(NOTIFYICONDATA);
		nid.hWnd = hWnd;
		nid.uID = 1;
		nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		nid.uCallbackMessage = WM_USER + 200;
		nid.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
		lstrcpy(nid.szTip, L"Hide My Desktop");
		Shell_NotifyIcon(NIM_ADD, &nid);
	}
	break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT  CALLBACK HideDialogProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		int widthWindow = GetSystemMetrics(SM_CXSCREEN);
		int heightWindow = GetSystemMetrics(SM_CYSCREEN);
		ShowCursor(FALSE);
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, widthWindow, heightWindow, SWP_SHOWWINDOW);
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		HDC hdc = GetWindowDC(hWnd);
		// Paint dialog with desktop wallpaper
		PaintDesktop(hdc);
		ReleaseDC(hWnd, hdc);
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_LBUTTONDBLCLK:
	{
		ShowCursor(TRUE);
		DestroyWindow(hWnd);
	}
	break;

	//ALT + anykey
	case WM_SYSKEYUP:   
	{
		ShowCursor(TRUE);
		DestroyWindow(hWnd);
	}
	break;

	case WM_COMMAND:
	{
		// Wparam - определяет источник сообщения: элемент управления или акселератор.
		// Lparam - идентификатор элемента, если это не акселератор.
		switch (LOWORD(wParam))
		{
			break;
		}
	}
	break;

	}
	return 0;
}
