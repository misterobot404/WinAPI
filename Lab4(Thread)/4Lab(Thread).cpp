// compile with: /EHsc
#include <iostream>
#include <windows.h>
// WinAPI function to create Thread (_beginthread, _beginthreadex, CreateThread, etc.)
#include <process.h>
// C++11 standard function to create portable Thread
// #include <thread>
using namespace std;

double container = 0;

unsigned __stdcall thread(void *)
{
	cout << "Поток запущен\n";
	try
	{
		while (container < 100000)
		{
			//int max value
			int randOne = rand() % 100000;
			int randTwo = rand() % 1000;

			if (randTwo == 0) throw -1;

			container += (double)randOne / (double)randTwo;
			if (container > 100000)
			{
				cout << "Контейнер заполнен\n";
			}
			Sleep(10);
		}
	}
	catch (...)
	{
		cout << "Ошибка в потоке\n";
	}
	return 1;
}

int	main()
{	
	setlocale(LC_ALL, "rus");
	system("color 0A ");

	HANDLE hThread[3];
	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, &thread, NULL, 0, NULL);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, &thread, NULL, 0, NULL);
	hThread[2] = (HANDLE)_beginthreadex(NULL, 0, &thread, NULL, 0, NULL);

	//WaitForSingleObject(hThread, INFINITE);
	//WaitForMultipleObjects(3, hThread, TRUE, INFINITE);

	//Analyze return code
	DWORD exitcode;
	while ((GetExitCodeThread(hThread[0], &exitcode) && exitcode == STILL_ACTIVE) || 
		(GetExitCodeThread(hThread[0], &exitcode) && exitcode == STILL_ACTIVE) || 
		(GetExitCodeThread(hThread[0], &exitcode) && exitcode == STILL_ACTIVE)) {};

	cout << "Все потоки завершили работу\n";
	system("pause");
	return 0;
}