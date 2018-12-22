/*
Выделить память под массив 1000х1000 элементов типа double и заполнить его случайными числами в интервале от 1 до 10,  
защитить страницы памяти с массивом от записи, выдать  сумму и среднее арифметическое элементов массива, 
дать команду на обнуление элементов и получить системное предупреждение о невозможности записи в массив.
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

	cout << "Выделение памяти под матрицу...\n";
	// MEM_COMMIT - Выполняется выделение страниц памяти для непосредственной работы с ними. Выделенные страницы заполняются нулями.
	// PAGE_READWRITE - Чтение и запись.
	double*matrix = (double*)VirtualAlloc(NULL, sizeMatrix * sizeMatrix * sizeof(double), MEM_COMMIT, PAGE_READWRITE);
	if (matrix == 0) {
		MessageBox(0, "Память не выделена", "ERROR", MB_ICONSTOP);
		return 0;
	}
	else
	{
		cout << "Память под матрицу " << sizeMatrix << "*" << sizeMatrix << " выделена\n";
	}

	cout << "Заполнение матрицы случайными числами...\n";
	for (int i = 0; i < sizeMatrix; ++i)
		for (int j = 0; j < sizeMatrix; ++j)
		{
			matrix[i * sizeMatrix + j] = 1 + rand() % 10;
		}
	cout << "Матрица заполнена\n";

	cout << "Установка защиты для памяти матрици...\n";
	// Последний аргумент — это указатель на DWORD. Эта переменная будет содержать уровень безопасности, которым обла¬дал участок до обращения к VirtualProtect.
	DWORD param;
	VirtualProtect(matrix, sizeof(double), PAGE_READONLY, &param);
	cout << "Защита установлена\n";

	cout << "Подсчет суммы всех элементов матрицы...\n";
	long long sumMatrix = 0;
	for (int i = 0; i < sizeMatrix; ++i)
		for (int j = 0; j < sizeMatrix; ++j)
		{
			sumMatrix += matrix[i * sizeMatrix + j];
		}
	cout << "Ответ: " << sumMatrix << "\n";

	cout << "Подсчет среднего арифметического элементов матрицы...\n";
	cout << "Ответ: " << (double)sumMatrix / (sizeMatrix* sizeMatrix) << "\n";

	cout << "Обнуление матрицы...\n";
	__try
	{	
		for (int i = 0; i < sizeMatrix; ++i)
			for (int j = 0; j < sizeMatrix; ++j)
			{
				matrix[i * sizeMatrix + j] = 0;
			}
		cout << "Обнуление матрицы -> DONE" << endl;
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		cout << "Обнуление матрицы -> ERROR" << endl;
	}

	system("pause");
	return 0;
}
