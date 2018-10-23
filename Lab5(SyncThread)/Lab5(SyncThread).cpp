#include <tchar.h>
#include <windows.h>
#include <process.h>

// Идентификаторы окон
#define ID_FIRSTCHILD	100
#define ID_SECONDCHILD	101
#define ID_THIRDCHILD	102

// Идентификаторы кнопок
#define EXIT 404
#define RUN 405

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

size_t i = 0;
SHELLEXECUTEINFO ShExecInfo;

unsigned __stdcall thread(void *)
{
	ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = L"C:\\Users\\miste\\Source\\Repos\\WinAPI\\Debug\\Lab5(SyncThread)Child.exe";
	ShExecInfo.lpParameters = L"";
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;

	ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
	--i;
	return 0;
}

unsigned __stdcall myWhile(void *)
{
	while (true)
	{
		while (i < 5)
		{
			_beginthreadex(NULL, 0, &thread, NULL, 0, NULL);
			++i;
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hThisInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszArgument,
	int nCmdShow)
{
	HWND hwnd;               /* This is the handle for our window */
	MSG messages;            /* Here messages to the application are saved */
	WNDCLASSEX wincl;        /* Data structure for the windowclass */

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

	/* Make the window visible on the screen */
	ShowWindow(hwnd, SW_HIDE);
	// ShowWindow (hwnd, nCmdShow);

	/* Run the message loop. It will run until GetMessage() returns 0 */
	while (GetMessage(&messages, NULL, 0, 0))
	{
		/* Translate virtual-key messages into character messages */
		TranslateMessage(&messages);
		/* Send message to WindowProcedure */
		DispatchMessage(&messages);
	}

	/* The program return-value is 0 - The value that PostQuitMessage() gave */
	return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure(HWND hWnd,		// дескриптор окошка
	UINT message,	// сообщение, посылаемое ОС
	WPARAM wParam, // параметры
	LPARAM lParam)	// сообщений, для последующего обращения
{
	static bool bCreated = false;

	if (lParam == WM_RBUTTONDOWN)
	{
		SetForegroundWindow(hWnd);
		POINT mouse;
		GetCursorPos(&mouse);
		HMENU hMenu = CreatePopupMenu();
		AppendMenu(hMenu, MF_ENABLED, RUN, L"Run");
		AppendMenu(hMenu, MF_ENABLED, EXIT, L"Exit");
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
		_beginthreadex(NULL, 0, &myWhile, NULL, 0, NULL);
		}
		break;

		case EXIT:
		{
			ShellExecute(NULL, NULL, L"taskkill", L"/F /IM Lab5(SyncThread)Child.exe", NULL, SW_HIDE);		
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
		nid.hIcon = LoadIcon(NULL, IDI_INFORMATION);
		lstrcpy(nid.szTip, L"SyncThread");
		Shell_NotifyIcon(NIM_ADD, &nid);
		// ShowWindow(hWnd, SW_HIDE);
		bCreated = true;
	}
	break;

	case WM_DESTROY:
	{
		if (bCreated)
		{
			NOTIFYICONDATA nid;
			memset(&nid, 0, sizeof(NOTIFYICONDATA));
			nid.cbSize = sizeof(NOTIFYICONDATA);
			nid.hWnd = hWnd;
			nid.uID = 1;
			Shell_NotifyIcon(NIM_DELETE, &nid);
		}
		PostQuitMessage(0);
	}
	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
