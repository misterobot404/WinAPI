#undef UNICODE
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#define _WIN32_WINDOWS 0x0501
#define _WIN32_IE 0x0600
#include <windows.h>
#include <iostream>

void main(void)
{   //������ ���������� ������ NOP 
	BYTE ja[5] = { 0x90, 0x90, 0x90, 0x90, 0x90 };
	DWORD *p; 

//�������� ������ � ��������� ������������ ������ ��������
HANDLE h = OpenProcess(PROCESS_VM_OPERATION	| PROCESS_VM_WRITE,	true, GetCurrentProcessId());
	
//��������� ������ �����
_asm{
	mov p,offset m002
    }

//�������� �� ������ ����� ������ ������� NOP (����� ������ �������� � ���������)
WriteProcessMemory(h, p, ja, 4, NULL);

m002:goto m001;
//-----------------------------------------------------
    //�������� ����. ������� ������� � ����� ������� ���� ���!
	MessageBox(0, "�� ������ � �������� ����!!!", "������ ������", 0);
//----------------------------------------------------		

m001:

	system("pause");
}