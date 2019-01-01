/*
�������� ������ ��� ������ 1000�1000 ��������� ���� double � ��������� ��� ���������� ������� � ��������� �� 1 �� 10,  
�������� �������� ������ � �������� �� ������, ������  ����� � ������� �������������� ��������� �������, 
���� ������� �� ��������� ��������� � �������� ��������� �������������� � ������������� ������ � ������.
*/
#define _CRT_SECURE_NO_WARNINGS
// compile with: /EHa
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include <iostream> 

using namespace std;

#define sizeMatrix 1000

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

	cout << "��������� ������ ��� �������...\n";
	// MEM_COMMIT - ����������� ��������� ������� ������ ��� ���������������� ������ � ����. ���������� �������� ����������� ������.
	// PAGE_READWRITE - ������ � ������.
	double*matrix = (double*)VirtualAlloc(NULL, sizeMatrix * sizeMatrix * sizeof(double), MEM_COMMIT, PAGE_READWRITE);
	if (matrix == 0) {
		MessageBox(0, "������ �� ��������", "ERROR", MB_ICONSTOP);
		return 0;
	}
	else
	{
		cout << "������ ��� ������� " << sizeMatrix << "*" << sizeMatrix << " ��������\n";
	}

	cout << "���������� ������� ���������� �������...\n";
	for (int i = 0; i < sizeMatrix; ++i)
		for (int j = 0; j < sizeMatrix; ++j)
		{
			matrix[i * sizeMatrix + j] = 1 + rand() % 10;
		}
	cout << "������� ���������\n";

	cout << "��������� ������ ��� ������ �������...\n";
	// ��������� �������� � ��� ��������� �� DWORD. ��� ���������� ����� ��������� ������� ������������, ������� ������� ������� �� ��������� � VirtualProtect.
	DWORD param;
	VirtualProtect(matrix, sizeof(double), PAGE_READONLY, &param);
	cout << "������ �����������\n";

	cout << "������� ����� ���� ��������� �������...\n";
	long long sumMatrix = 0;
	for (int i = 0; i < sizeMatrix; ++i)
		for (int j = 0; j < sizeMatrix; ++j)
		{
			sumMatrix += matrix[i * sizeMatrix + j];
		}
	cout << "�����: " << sumMatrix << "\n";

	cout << "������� �������� ��������������� ��������� �������...\n";
	cout << "�����: " << (double)sumMatrix / (sizeMatrix* sizeMatrix) << "\n";

	cout << "��������� �������...\n";
	__try
	{	
		for (int i = 0; i < sizeMatrix; ++i)
			for (int j = 0; j < sizeMatrix; ++j)
			{
				matrix[i * sizeMatrix + j] = 0;
			}
		cout << "��������� ������� -> DONE" << endl;
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		cout << "��������� ������� -> ERROR" << endl;
	}

	system("pause");
	return 0;
}
