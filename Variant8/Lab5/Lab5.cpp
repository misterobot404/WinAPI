/*
Один поток читает файл, указанный в первом параметре программы, второй поток читает файл, указанный во втором параметре программы.
Третий поток сравнивает файлы и выводит на экран номера и значения несовпадающих байтов.
*/

#include <iostream>
#include <windows.h>
#include <process.h>
#include <fstream>
#include <cstdlib>
using namespace std;

////// GLOBAL VARIABLE //////
// События завершения считывания и анализа байтов
HANDLE hEventRead[2], hEventСomparison[2];
// Потоrи для чтения байтов из файлов
ifstream filestream1;
ifstream filestream2;
// Хранение извлеченного байта из первого и второго потока
char byte1;
char byte2;
// Состояние окончания файлов
bool filestream1Compl;
bool filestream2Compl;
// Состояние окончаник сравнения
bool comparisonCompl;
///////////////////////////

// Побайтовое чтение первого файла
unsigned __stdcall read1(void* stream)
{
	filestream1Compl = false;
	while (!comparisonCompl)
	{
		// Поток comparison закончил сравнение байтов, извлекаем дальше
		WaitForSingleObject(hEventСomparison[0], INFINITE);

		if (!filestream1.get(byte1)) filestream1Compl = true;

		// Сигнализируем о завершении извлечения байта
		SetEvent(hEventRead[0]);
	}
	return 0;
}

// Побайтовое чтение второго файла
unsigned __stdcall read2(void* stream)
{
	filestream2Compl = false;
	while (!comparisonCompl)
	{
		WaitForSingleObject(hEventСomparison[1], INFINITE);
		if (!filestream2.get(byte2)) filestream2Compl = true;
		SetEvent(hEventRead[1]);
	}
	return 0;
}

// Сравнение байтов
unsigned __stdcall comparison(void*)
{
	// Хранение номера сравниваемого байта
	size_t indexByte = 0;

	comparisonCompl = false;

	while (!comparisonCompl)
	{
		// Третий параметр TRUE, если нужно ждать сигнализации всех событий, FALSE если любого события из массива
		WaitForMultipleObjects(2, hEventRead, TRUE, INFINITE);

		// Если первый поток и второй поток завершили работу выходим
		if (filestream1Compl == true && filestream2Compl == true)
		{
			comparisonCompl = true;
			// Для каждого потока сообщаем что их байты проанализированы
			SetEvent(hEventСomparison[0]);
			SetEvent(hEventСomparison[1]);
			break;
			
		}

		++indexByte;
		if (byte1 != byte2)
		{
			cout << "*НАЙДЕНО НЕСОВПАДЕНИЕ*" << endl;
			cout << "Номер не совпадающего байта: " << indexByte << endl;

			cout << "Байт из первого файла (в виде HEX): ";
			if (filestream1Compl) cout << "Отсутствует";
			else cout << hex << (int)byte1 << " (" << byte1 << ")";
			cout << endl;

			cout << "Байт из второго файла (в виде HEX): ";
			if (filestream2Compl) cout << "Отсутствует";
			else cout << hex << (int)byte2 << " (" << byte2 << ")";
			cout << endl << endl;
		}
		
		// Для каждого потока сообщаем что их байты проанализированы
		SetEvent(hEventСomparison[0]);
		SetEvent(hEventСomparison[1]);
	}
	return 0;
}

int	main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	system("color 0A");

	// если передаем аргументы, то argc будет больше 1 (в зависимости от кол-ва аргументов)
	if (argc != 3)
	{
		cout << "При запуске программы передайте два аргумента: путь до первого и второго файла." << endl;
		system("pause");
		return -1;
	}

	cout << "Примечание: для корректной работы программы сравниваемые файлы должны быть в кодировке Windows-1251 (или другие однобайтовые кодировки)." << endl << endl;

	// Открытие поток по путям из параметров
	filestream1.open(argv[1], ios::binary);
	filestream2.open(argv[2], ios::binary);

	// Проверка открытия потоков
	if (filestream1 && filestream2)
	{
		// Инициализация событий
		// 2 пар: Вид сброса событий false - РУЧНОЙ, true - авто
		// 3 пар: Начальное состояние события
		hEventRead[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
		hEventRead[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
		hEventСomparison[0] = CreateEvent(NULL, FALSE, TRUE, NULL);
		hEventСomparison[1] = CreateEvent(NULL, FALSE, TRUE, NULL);

		HANDLE hThread[3];
		// Потоки извлечения
		// Передаём потокам поток на первый и второй файл
		hThread[0] = (HANDLE)_beginthreadex(NULL, 0, &read1, &filestream1, 0, NULL);
		hThread[1] = (HANDLE)_beginthreadex(NULL, 0, &read2, &filestream2, 0, NULL);
		// Поток сравнения
		hThread[2] = (HANDLE)_beginthreadex(NULL, 0, &comparison, NULL, 0, NULL);

		// Ожидание завершения всех потоков
		WaitForMultipleObjects(3, hThread, TRUE, INFINITE);
		cout << "Все потоки завершили работу." << endl;
		filestream1.close();
		filestream2.close();
	}
	else cout << "Ошибка открытия файлов!" << endl;

	system("pause");
	return 0;
}
