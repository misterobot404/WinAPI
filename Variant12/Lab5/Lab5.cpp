/*
Имеется файл F1, в котором записано 20 слов (можно больше). 
Три потока генерируют случайные числа в диапазоне 0 – 100. 
Если сгенерированное число больше 90, поток генерирует случайное число n от 1  до 20, 
открывает файл F1, берет из него слово под номером n, открывает файл F2 и вписывает взятое слово в него файлы F1 и F2 закрываются. 
Каждый поток должен записать в файл F2 по три слова. Полученное предложение приложите в отчет.
*/
#include <iostream>
#include <windows.h>
#include <process.h>
#include <string>
#include <fstream>
#include <mutex>
#include <random>
using namespace std;

mutex writeLock;
unsigned __stdcall readWrite(void *);
int getRandomInt(int start, int end);


int	main()
{
	setlocale(LC_ALL, "rus");
	system("color 0A ");

	HANDLE hThread[3];

	for (size_t i = 0; i < 3; i++)
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, &readWrite, NULL, 0, NULL);
	
	cout << "Все потоки запущены...\n";

	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);

	cout << "Все потоки завершили работу\n";
	system("pause");
	return 0;
}


unsigned __stdcall readWrite(void *)
{
	size_t count = 0;

	while (count<3)
	{
		int rndNum = 1 + rand() % 100;
		if (rndNum > 90)
		{
			int rndWord = getRandomInt(1,20);

			ifstream file1("text1.txt");
			if (!file1)
			{
				cout << "Файл не найден\nError\n";
				system("pause");
				exit(0);
			}

			string  word;
			for (size_t i = 0; i < rndWord; i++)
				getline(file1, word, ' ');			
			file1.close();

			writeLock.lock();
			ofstream file2;						
			file2.open("text2.txt", ios::app);
			file2 << word << ' ';
			file2.close();
			writeLock.unlock();

			count++;
		}
		Sleep(200);
	}
	return 0;
}

int getRandomInt(int start, int end)
{
	default_random_engine g(chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> distribution(start, end);
	return  distribution(g);
}