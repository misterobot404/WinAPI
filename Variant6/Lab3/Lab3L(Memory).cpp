#include <windows.h>
#include <string>
using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, // ������������� ���������� 
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{	
	byte *ptr = (byte*)hInstance; // ������� byte ��������� �� ������ ������� ������ ���������
	VirtualProtect(ptr, sizeof(byte), PAGE_READONLY, NULL); // ����������� ��� ������ ��� ������� ������

	string str; 

	for (size_t i = 0; i < 5; i++) 
	{
		str += to_string(ptr[i]);
		str += "   ";
	}
		
	MessageBox(NULL, LPSTR(str.c_str()),"������ 5 ������ ��� ��������", 0);

	return 0;
}