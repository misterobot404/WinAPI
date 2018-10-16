// compile with: /EHa
#include <iostream>
#include <windows.h>
// WinAPI function to create Thread (_beginthread, _beginthreadex, CreateThread, etc.)
#include <process.h>
// C++11 standard function to create portable Thread
// #include <thread>
using namespace std;

//HANDLE e;
HANDLE exitCodeHandleOne;
HANDLE exitCodeHandleTwo;
HANDLE exitCodeHandleThree;
double container = 0;

void myException(unsigned int u, EXCEPTION_POINTERS* pExp)
{
	throw u;
}

void threadOne(void *)
{
	cout << "Первый поток запущен\n";
	exitCodeHandleOne = GetCurrentThread();
	try
	{
		_set_se_translator(myException);
		while (container < 100000)
		{
			int randOne = rand() % 1000;
			int randTwo = 1 + rand() % 100;
			container += (double)randOne / (double)randTwo;
			if (container > 100000)
			{
				cout << "Контейнер заполнен первым потоком\n";
			}
			Sleep(2);
		}
	}
	catch (unsigned int u)
	{
		cout << "Ошибка в первом потоке\n";
	}
}

void threadTwo(void *)
{
	cout << "Второй поток запущен\n";
	//exitCodeHandleTwo = GetCurrentThread();
	try
	{
		_set_se_translator(myException);
		while (container < 100000)
		{
			int randOne = rand() % 1000;
			int randTwo = 1 + rand() % 100;
			container += (double)randOne / (double)randTwo;
			if (container > 100000)
			{
				cout << "Контейнер заполнен вторым потоком\n";			
			}
			Sleep(2);
		}
	}
	catch (unsigned int u)
	{
		cout << "Ошибка во втором потоке\n";
	}
}

void threadThree(void *)
{
	cout << "Третий поток запущен\n";
	//exitCodeHandleThree = GetCurrentThread();
	try
	{
		_set_se_translator(myException);
		while (container < 100000)
		{
			int randOne = rand() % 1000;
			int randTwo = rand() % 100;
			container += randOne / randTwo;
			if (container > 100000)
			{
				cout << "Контейнер заполнен третьим потоком\n";
				//SetEvent(e);
			}
			Sleep(1);
		}
		
	}
	catch (unsigned int u)
	{
		cout << "Ошибка в третьем потоке\n";
	}
}

int	main()
{	
	setlocale(LC_ALL, "rus");
	system("color 0A ");
	//e = CreateEvent(NULL, FALSE, FALSE, NULL);

	_beginthread(threadOne, 0, NULL);	
	//_beginthread(threadTwo, 0, NULL);
	_beginthread(threadThree, 0, NULL);

	//WaitForSingleObject(e, INFINITE);

	Sleep(500);

	while (true)
	{
		DWORD exitcode;
		GetExitCodeThread(exitCodeHandleOne, &exitcode);
		if (exitcode != STILL_ACTIVE) break;
	}
	cout << "Все потоки завершили работу\n";
	system("pause");
	return 0;
}