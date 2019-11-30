/*
���������� �������� ������� ������ �������� 32 ��� �� �������: 900 000, 1 000 000 � 3 000 000. 
��������� ��� ������� ���������. �������� �� ������ � ����������� ��������. ��� ������������� ������ � ����������� �� � ������ �� ���� ���������.
*/
// compile with: /EHa
#include <windows.h>
#include <locale.h>
#include <iostream>

using namespace std;


int filter(unsigned int code, struct _EXCEPTION_POINTERS *ep) {

	if (code == EXCEPTION_ACCESS_VIOLATION) {
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else {
		return EXCEPTION_CONTINUE_SEARCH;
	};
}

int main()
{
	setlocale(LC_ALL, "rus");
	system("color 0A ");

	// ����� ������ �� 32 �� = 32000 ���� = 8000 * 4 byte = 8000 * sizeof(int)
	const size_t blockByteSize = 8000 * sizeof(int);
	const size_t blockElementSize = blockByteSize / sizeof(int);
	// ������ ���������� �� ��� ����� ���������� ������
	int* arrayPointer[3];

	// �� �������: 900 000, 1 000 000 � 3 000 000... 
	cout << "��������� �������� ������ �������� 32�� ";
	// MEM_COMMIT - ����������� ��������� ������� ������ ��� ���������������� ������ � ����. ���������� �������� ����������� ������.
	// PAGE_READWRITE - ����� �� ������ � ������.
	arrayPointer[0] = (int*)VirtualAlloc(NULL, blockByteSize, MEM_COMMIT, PAGE_READWRITE);
	arrayPointer[1] = (int*)VirtualAlloc(NULL, blockByteSize, MEM_COMMIT, PAGE_READWRITE);
	arrayPointer[2] = (int*)VirtualAlloc(NULL, blockByteSize, MEM_COMMIT, PAGE_READWRITE);

	if (arrayPointer[0] == NULL || arrayPointer[1] == NULL || arrayPointer[2] == NULL) {
		MessageBox(0, "������ �� ��������", "ERROR", MB_ICONSTOP);
		return 0;
	}
	else
	{
		cout << "������ ��������." << endl;
	}

	cout << "���������� �������� ������ ���������... ";
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < blockElementSize; ++j)
		{
			arrayPointer[i][j] = 1;
		}
	cout << "������ ���������." << endl;

	cout << "��������� ������ ��� ������ �������... ";
	// ��������� �������� � ��� ��������� �� DWORD. ��� ���������� ����� ��������� ������� ������������, ������� ������� ������� �� ��������� � VirtualProtect.
	DWORD param;
	VirtualProtect(arrayPointer[0], sizeof(int), PAGE_READONLY, &param);
	VirtualProtect(arrayPointer[1], sizeof(int), PAGE_READONLY, &param);
	VirtualProtect(arrayPointer[2], sizeof(int), PAGE_READONLY, &param);
	cout << "������ �����������." << endl;

	cout << "��������� �������� ������... ";
	__try
	{	
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < blockElementSize; ++j)
			{
				arrayPointer[i][j] = 0;
			}
		cout << "" << endl;
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		cout << "ERROR! Msg: EXCEPTION_ACCESS_VIOLATION" << endl;
	}

	system("pause");
	return 0;
}
