/*
Необходимо выделить участки памяти размером 32 Кбт по адресам: 900 000, 1 000 000 и 3 000 000. 
Заполнить эти участки единицами. Защитить от записи и попробывать очистить. При возникновении ошибки – перехватить ее и выдать об этом сообщение.
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

	// Блоки памяти по 32 Кб = 32000 Байт = 8000 * 4 byte = 8000 * sizeof(int)
	const size_t blockByteSize = 8000 * sizeof(int);
	const size_t blockElementSize = blockByteSize / sizeof(int);
	// Массив указателей на три блока выделяемой памяти
	int* arrayPointer[3];

	// по адресам: 900 000, 1 000 000 и 3 000 000... 
	cout << "Выделение участков памяти размером 32Кб ";
	// MEM_COMMIT - Выполняется выделение страниц памяти для непосредственной работы с ними. Выделенные страницы заполняются нулями.
	// PAGE_READWRITE - Режим на чтение и запись.
	arrayPointer[0] = (int*)VirtualAlloc(NULL, blockByteSize, MEM_COMMIT, PAGE_READWRITE);
	arrayPointer[1] = (int*)VirtualAlloc(NULL, blockByteSize, MEM_COMMIT, PAGE_READWRITE);
	arrayPointer[2] = (int*)VirtualAlloc(NULL, blockByteSize, MEM_COMMIT, PAGE_READWRITE);

	if (arrayPointer[0] == NULL || arrayPointer[1] == NULL || arrayPointer[2] == NULL) {
		MessageBox(0, "Память не выделена", "ERROR", MB_ICONSTOP);
		return 0;
	}
	else
	{
		cout << "Память выделена." << endl;
	}

	cout << "Заполнение участков памяти единицами... ";
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < blockElementSize; ++j)
		{
			arrayPointer[i][j] = 1;
		}
	cout << "Память заполнена." << endl;

	cout << "Установка защиты для памяти матрици... ";
	// Последний аргумент — это указатель на DWORD. Эта переменная будет содержать уровень безопасности, которым обла¬дал участок до обращения к VirtualProtect.
	DWORD param;
	VirtualProtect(arrayPointer[0], sizeof(int), PAGE_READONLY, &param);
	VirtualProtect(arrayPointer[1], sizeof(int), PAGE_READONLY, &param);
	VirtualProtect(arrayPointer[2], sizeof(int), PAGE_READONLY, &param);
	cout << "Защита установлена." << endl;

	cout << "Обнуление участков памяти... ";
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
