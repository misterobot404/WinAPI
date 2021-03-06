/*
Выделить память под два массива 1000х500 и 500х1000 элементов типа int и заполнить их случайными числами в интервале от 0 до 100.
 Защитить от записи страницы первого массива.
 Перемножить эти два массива и выдать результат на экран.Перехватить обработчик исключений.
 Дать команду на обнуление массивов. 
 На исключение о защите памяти выдать сообщение с указанием названия массива, который не удалось обнулить.
*/

#define _CRT_SECURE_NO_WARNINGS
// compile with: /EHa
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include <iostream> 

using namespace std;

#define sizeOne 25
#define sizeTwo 25

int filter(unsigned int code, struct _EXCEPTION_POINTERS *ep) {
	
	if (code == EXCEPTION_ACCESS_VIOLATION) {	
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else {		
		return EXCEPTION_CONTINUE_SEARCH;
	};
}

/*void myException(unsigned int u, EXCEPTION_POINTERS* pExp)
{
	throw u;
}*/

int main()
{
	setlocale(LC_ALL, "rus");
	system("color 0A ");

	cout << "Выделение памяти под первую матрицу...\n";
	// MEM_COMMIT - Выполняется выделение страниц памяти для непосредственной работы с ними. Выделенные страницы заполняются нулями.
	// PAGE_READWRITE - Чтение и запись.
	int*firstMatrix = (int*)VirtualAlloc(NULL, sizeTwo * sizeOne * sizeof(int), MEM_COMMIT, PAGE_READWRITE);
	if (firstMatrix == 0) {
		MessageBox(0, L"Память не выделена", L"ERROR", MB_ICONSTOP);
		return 0;
	}
	else
	{
		cout << "Память под матрицу " << sizeTwo << "*" << sizeOne << " выделена\n";
	}

	cout << "Выделение памяти под вторую матрицу...\n";
	int*secondMatrix = (int*)VirtualAlloc(NULL, sizeOne * sizeTwo * sizeof(int), MEM_COMMIT, PAGE_READWRITE);
	if (secondMatrix == 0) {
		MessageBox(0, L"Память не выделена", L"ERROR", MB_ICONSTOP);
		return 0;
	}
	else
	{
		cout << "Память под матрицу " << sizeOne << "*" << sizeTwo << " выделена\n";
	}

	cout << "Заполнение первой матрици случайными числами...\n";
	for (int i = 0; i < sizeTwo; ++i)
		for (int j = 0; j < sizeOne; ++j)
		{
			firstMatrix[i * sizeOne + j] = rand() % 100;
		}
	cout << "Первая матрица заполнена\n";

	cout << "Заполнение второй матрици случайными числами...\n";
	for (int i = 0; i < sizeOne; ++i)
		for (int j = 0; j < sizeTwo; ++j)
		{
			secondMatrix[i * sizeTwo + j] = rand() % 100;
		}
	cout << "Вторая матрица заполнена\n";

	cout << "Установка защиты для памяти первой матрици...\n";
	DWORD param;
	// Последний аргумент — это указатель на DWORD. Эта переменная будет содержать уровень безопасности, которым обла¬дал участок до обращения к VirtualProtect.
	VirtualProtect(firstMatrix, sizeof(double), PAGE_READONLY, &param);
	cout << "Защита установлена\n";

	cout << "Вывод произведения первой и второй матриц...\n";
	int sizeMultipliedMatrix = sizeOne * sizeTwo;
	for (int i = 0; i < sizeMultipliedMatrix; ++i)
	{
		cout << secondMatrix[i] * firstMatrix[i] << " ";
	}
	cout << endl;

	cout << "Обнуление массивов...\n";
	bool EXEP = false;

	__try
	{
		//_set_se_translator(myException);		
		for (int i = 0; i < sizeOne; ++i)
			for (int j = 0; j < sizeTwo; ++j)
			{
				firstMatrix[i * sizeTwo + j] = 0;
			}
	}
	/*catch (unsigned int u)
	{		
	}*/
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{	
		cout << "Обнуление первого массива -> ERROR" << endl;
		EXEP = true;
	}
	if (EXEP==false)
	{
		cout << "Обнуление первой матрицы -> DONE" << endl;
	} 
	else
	{
		EXEP = false;
	}

	__try
	{
		//_set_se_translator(myException);
		for (int i = 0; i < sizeOne; ++i)
			for (int j = 0; j < sizeTwo; ++j)
			{
				secondMatrix[i * sizeTwo + j] = 0;
			}
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		cout << "Обнуление второй матрицы -> ERROR";
	}
	if (EXEP == false)
	{
		cout << "Обнуление второй матрици -> DONE" << endl;
	}	

	system("pause");
	return 0;
}

