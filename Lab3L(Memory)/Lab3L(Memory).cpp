#include <windows.h>
#include <string>
LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{	
	HWND hwnd;

	byte *ptr = (byte*)hInstance;
	VirtualProtect(ptr, sizeof(byte), PAGE_READONLY, NULL);
	
	MSG msg;
	WNDCLASS w;
	memset(&w, 0, sizeof(WNDCLASS));
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = WndProc;
	w.hInstance = hInstance;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.lpszClassName = "My Class";
	RegisterClass(&w);
	hwnd = CreateWindow("My Class", "My title", WS_OVERLAPPEDWINDOW,
		300, 200, 200, 180, NULL, NULL, hInstance, NULL);

	std::string ch;
	std::string fnl;
	
	ch = std::to_string(ptr[0]);

	for (size_t i = 1; i < 5; i++) 
	{
		ch += "   ";
		ch += std::to_string(ptr[i]);
	}
		

	MessageBox(hwnd, LPSTR(ch.c_str()),"Первые 5 байтов код. сегмента", 0);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LONG WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
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