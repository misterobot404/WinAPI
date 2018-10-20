#include <iostream>
#include <windows.h>
// WinAPI function to create Thread (_beginthread, _beginthreadex, CreateThread, etc.)
#include <process.h>
// C++11 standard function to create portable Thread
// #include <thread>
using namespace std;

//HANDLE exitCodeHandle[3];

unsigned __stdcall thread(void *)
{
	cout << "Поток запущен\n";
	//exitCodeHandle[0] = GetCurrentThread();
	while (true)
	{
		int random = rand() % 1000;
		if (random > 900)
		{
			break;
		}
	}
	cout << "Поток завершен\n";
	return 0;
}

int	main()
{
	setlocale(LC_ALL, "rus");
	system("color 0A ");

	//exitCodeHandle[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
	//exitCodeHandle[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
	//exitCodeHandle[2] = CreateEvent(NULL, FALSE, FALSE, NULL);

	HANDLE hThread[3];
	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, &thread, NULL, 0, NULL);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, &thread, NULL, 0, NULL);
	hThread[2] = (HANDLE)_beginthreadex(NULL, 0, &thread, NULL, 0, NULL);


	//WaitForSingleObject(hThread, INFINITE);
	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);

	system("pause");
	return 0;
}