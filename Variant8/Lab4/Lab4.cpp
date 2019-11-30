/*
Пять потоков генерируют случайные целые числа в диапазоне от 1 до 49. Шестой поток – анализирует эти числа. 
Если появляется пара одинаковых чисел – выводится сообщение ПАРА и номера потоков этой пары. Если три числа одинаковы – ТРИ, Четыре – ЧЕТЫРЕ и пять – ПЯТЬ. 
Через 60 секунд работы программа завершается. Если не было ни одного совпадения – выводится об этом сообщение.
*/

// compile with: /EHsc
#include <iostream>
#include <windows.h>
#include <string>
#include <random>
// WinAPI function to create Thread (_beginthread, _beginthreadex, CreateThread, etc.)
#include <process.h>
// C++11 standard function to create portable Thread
// #include <thread>
using namespace std;

////// GLOBAL VARIABLE //////
// Таймер, потоки генерирующие новые случайные значения будут ждать завершение таймера
HANDLE hTimer;
DWORD exitcode;
// Массив, куда потоки будут записывать значения
size_t arrRandomValue[5];
// Обьекты рандомизации
default_random_engine generator;
uniform_int_distribution<int> distribution(1, 49);
////////////////////////////

// Прототипы функций
string getMaxCountEqual();

// Таймер
unsigned __stdcall timer(void*)
{
	cout << "Таймер запущен. Осталось 60 секунд." << endl;
	Sleep(30000);
	cout << "Осталось 30 секунд." << endl;
	Sleep(30000);
	cout << "Время вышло. Таймер выключен." << endl;
	return 1;
}

// Потоки генирирующие случайные целые числа в диапазоне от 1 до 49
unsigned __stdcall thread1(void*)
{ 
	cout << "Поток 1 запущен" << endl;
	while ((GetExitCodeThread(hTimer, &exitcode) && exitcode == STILL_ACTIVE))
	{
			arrRandomValue[0] = distribution(generator);
			Sleep(50);
	}
	return 1;
}
unsigned __stdcall thread2(void*)
{
	cout << "Поток 2 запущен" << endl;
	while ((GetExitCodeThread(hTimer, &exitcode) && exitcode == STILL_ACTIVE))
	{
		arrRandomValue[1] = distribution(generator);
		Sleep(50);
	}
	return 1;
}
unsigned __stdcall thread3(void*)
{
	cout << "Поток 3 запущен" << endl;
	while ((GetExitCodeThread(hTimer, &exitcode) && exitcode == STILL_ACTIVE))
	{
		arrRandomValue[2] = distribution(generator);
		Sleep(50);
	}
	return 1;
}
unsigned __stdcall thread4(void*)
{
	cout << "Поток 4 запущен" << endl;
	while ((GetExitCodeThread(hTimer, &exitcode) && exitcode == STILL_ACTIVE))
	{
		arrRandomValue[3] = distribution(generator);
		Sleep(50);
	}
	return 1;
}
unsigned __stdcall thread5(void*)
{
	cout << "Поток 5 запущен" << endl;
	while ((GetExitCodeThread(hTimer, &exitcode) && exitcode == STILL_ACTIVE))
	{
		arrRandomValue[4] = distribution(generator);
		Sleep(50);
	}
	return 1;
}

// Анализ чисел
unsigned __stdcall comparison(void*)
{
	cout << "Поток анализа чисел запущен" << endl;
	while ((GetExitCodeThread(hTimer, &exitcode) && exitcode == STILL_ACTIVE))
	{
		string count = getMaxCountEqual();
		if (count != "") cout << count << endl;
		Sleep(200);
	}
	return 1;
}
// Количество одинаковых чисел в массиве
string getMaxCountEqual()
{
	// Делаем копию массива. Мы не можем работать с оригиналом, тк он постоянно изменяться
	size_t arrRandomValue_Temp[5];
	memcpy(arrRandomValue_Temp, arrRandomValue, sizeof(size_t) * 5);

	string res = "";
	string res_temp = "";
	// Количество повторений числа
	size_t maxCount = 1;
	size_t count = 0;

	for (size_t i = 0; i < 5; i++, count = 0, res_temp = "")
	{
		// Нахождение количество повторений для числа
		for (size_t j = 0; j < 5; j++)
		{
			if (arrRandomValue_Temp[i] == arrRandomValue_Temp[j]) {
				count++;
				res_temp += " " + to_string(j + 1);
			}
		}
		if (count > maxCount) {
			maxCount = count;
			res = res_temp;
		};
	};

	if (maxCount == 2) res = "ПАРА Потоки:" + res;
	else if (maxCount == 3) res = "ТРИ Потоки:" + res;
	else if (maxCount == 4) res = "ЧЕТЫРЕ Потоки:" + res;
	else if (maxCount == 5) res = "ПЯТЬ Потоки:" + res;

	return res;
}

int	main()
{
	setlocale(LC_ALL, "rus");
	system("color 0A");

	hTimer = (HANDLE)_beginthreadex(NULL, 0, &timer, NULL, 0, NULL);
	Sleep(1000);
	HANDLE hThread[6];
	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, &thread1, NULL, 0, NULL);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, &thread2, NULL, 0, NULL);
	hThread[2] = (HANDLE)_beginthreadex(NULL, 0, &thread3, NULL, 0, NULL);
	hThread[3] = (HANDLE)_beginthreadex(NULL, 0, &thread4, NULL, 0, NULL);
	hThread[4] = (HANDLE)_beginthreadex(NULL, 0, &thread5, NULL, 0, NULL);
	Sleep(1000);
	hThread[5] = (HANDLE)_beginthreadex(NULL, 0, &comparison, NULL, 0, NULL);

	// Ожидание завершения всех потоков
	WaitForMultipleObjects(6, hThread, TRUE, INFINITE);

	cout << "Все потоки завершили работу." << endl;
	system("pause");
	return 0;
}
