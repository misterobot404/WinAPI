#include <iostream>
#include <windows.h>
#include <ctime>
#include <mutex>
// WinAPI function to create Thread (_beginthread, _beginthreadex, CreateThread, etc.)
#include <process.h>
using namespace std;

constexpr size_t matrixSize = 7;
constexpr int randMin = 1;
constexpr int randMax = 5;
mutex mutexThread;

int Matrix[matrixSize][matrixSize];

unsigned __stdcall ArithmeticMean(void *)
{
	int sumAllElements = 0;

	for (size_t i = 0; i < matrixSize; ++i)
	{
		for (size_t j = 0; j < matrixSize; ++j)
		{
			sumAllElements += Matrix[i][j];
		}
		if (i == matrixSize / 2)
		{
			mutexThread.lock();
			cout << "Вычислени среднего арифметического -> 50%\n";
			mutexThread.unlock();
		}
	}
	mutexThread.lock();
	cout << "Среднее арифметическое -> " << double(sumAllElements) / (matrixSize*matrixSize) << "\n";
	mutexThread.unlock();
	return 0;
}

unsigned __stdcall GeometricMean(void *)
{
	long long multiplicationAllElements = 1;

	for (size_t i = 0; i < matrixSize; ++i)
	{
		for (size_t j = 0; j < matrixSize; ++j)
		{
			multiplicationAllElements *= Matrix[i][j];
		}
		if (i == matrixSize / 2)
		{
			mutexThread.lock();
			cout << "Вычислени среднего геометрического -> 50%\n";
			mutexThread.unlock();
		}
	}
	mutexThread.lock();
	cout << "Среднее геометрическое -> " << pow(multiplicationAllElements, 1.0 / (matrixSize*matrixSize)) << "\n";
	mutexThread.unlock();

	return 0;
}

unsigned __stdcall SquareMean(void *)
{
	int sumAllElementsInSquare = 0;

	for (size_t i = 0; i < matrixSize; ++i)
	{
		for (size_t j = 0; j < matrixSize; ++j)
		{
			sumAllElementsInSquare += Matrix[i][j] * Matrix[i][j];
		}
		if (i == matrixSize / 2)
		{
			mutexThread.lock();
			cout << "Вычислени среднего квадратического -> 50%\n";
			mutexThread.unlock();
		}
	}
	mutexThread.lock();
	cout << "Среднее квадратическое -> " << sqrt(sumAllElementsInSquare / (matrixSize * matrixSize)) << "\n";
	mutexThread.unlock();
	return 0;
}

int	main()
{
	setlocale(LC_ALL, "rus");
	system("color 0A ");
	srand(time(NULL));

	for (size_t i = 0; i < matrixSize; ++i)
	{
		for (size_t j = 0; j < matrixSize; ++j)
		{
			Matrix[i][j] = randMin + rand() % (randMax - randMin);
		}
	}

	HANDLE hThread[3];
	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, &ArithmeticMean, NULL, 0, NULL);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, &GeometricMean, NULL, 0, NULL);
	hThread[2] = (HANDLE)_beginthreadex(NULL, 0, &SquareMean, NULL, 0, NULL);
	cout << "Все потоки запущены\n";

	// Analyze return code
	DWORD exitcode;
	while ((GetExitCodeThread(hThread[0], &exitcode) && exitcode == STILL_ACTIVE) ||
		(GetExitCodeThread(hThread[1], &exitcode) && exitcode == STILL_ACTIVE) ||
		(GetExitCodeThread(hThread[2], &exitcode) && exitcode == STILL_ACTIVE)) {
	};

	cout << "Все потоки завершили работу\n";
	system("pause");
	return 0;
}