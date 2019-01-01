#include <windows.h>
#include <string>
using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, // Идентификатор приложения 
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{	
	byte *ptr = (byte*)hInstance; // Создаем byte указатель на начало область памяти программы
	VirtualProtect(ptr, sizeof(byte), PAGE_READONLY, NULL); // Разблокирем для чтения эту область памяти

	string str; 

	for (size_t i = 0; i < 5; i++) 
	{
		str += to_string(ptr[i]);
		str += "   ";
	}
		
	MessageBox(NULL, LPSTR(str.c_str()),"Первые 5 байтов код сегмента", 0);

	return 0;
}