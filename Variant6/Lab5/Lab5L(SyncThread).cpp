#include <windows.h>
#include <iostream>
#include "tlhelp32.h"
using namespace std;

#include <windows.h>
LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{	
	if (__argv[1])
	{
		if (strcmp("/R", __argv[1]) == 0)
		{
			ShellExecute(NULL, NULL, "taskkill", "/F /IM Lab5L(SyncThread).exe", NULL, SW_HIDE);
		}
	}
	
	HANDLE hSnap;
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 proc;

	if (Process32First(hSnap, &proc))
	{
		int countProc = 0;
		do {
			if (strcmp("Lab5L(SyncThread).exe", proc.szExeFile) == 0)
				++countProc;
		} while (Process32Next(hSnap, &proc));
		if (countProc > 3)
		{
			return 0;
		}
	}

	HWND hwnd;
	MSG msg;
	WNDCLASS w;
	memset(&w, 0, sizeof(WNDCLASS));
	w.lpfnWndProc = WndProc;
	w.lpszClassName = "My Class";
	RegisterClass(&w);
	hwnd = CreateWindow("My Class", "My title", WS_OVERLAPPEDWINDOW,
		300, 200, 200, 180, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
	switch (Message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Message, wparam, lparam);
	}
	return 0;
}