/*
���� ������� ���������� ��������� ����� ����� � ��������� �� 1 �� 49. ������ ����� � ����������� ��� �����. 
���� ���������� ���� ���������� ����� � ��������� ��������� ���� � ������ ������� ���� ����. ���� ��� ����� ��������� � ���, ������ � ������ � ���� � ����. 
����� 60 ������ ������ ��������� �����������. ���� �� ���� �� ������ ���������� � ��������� �� ���� ���������.
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
// ������, ������ ������������ ����� ��������� �������� ����� ����� ���������� �������
HANDLE hTimer;
DWORD exitcode;
// ������, ���� ������ ����� ���������� ��������
size_t arrRandomValue[5];
// ������� ������������
default_random_engine generator;
uniform_int_distribution<int> distribution(1, 49);
////////////////////////////

// ��������� �������
string getMaxCountEqual();

// ������
unsigned __stdcall timer(void*)
{
	cout << "������ �������. �������� 60 ������." << endl;
	Sleep(30000);
	cout << "�������� 30 ������." << endl;
	Sleep(30000);
	cout << "����� �����. ������ ��������." << endl;
	return 1;
}

// ������ ������������ ��������� ����� ����� � ��������� �� 1 �� 49
unsigned __stdcall thread1(void*)
{ 
	cout << "����� 1 �������" << endl;
	while ((GetExitCodeThread(hTimer, &exitcode) && exitcode == STILL_ACTIVE))
	{
			arrRandomValue[0] = distribution(generator);
			Sleep(50);
	}
	return 1;
}
unsigned __stdcall thread2(void*)
{
	cout << "����� 2 �������" << endl;
	while ((GetExitCodeThread(hTimer, &exitcode) && exitcode == STILL_ACTIVE))
	{
		arrRandomValue[1] = distribution(generator);
		Sleep(50);
	}
	return 1;
}
unsigned __stdcall thread3(void*)
{
	cout << "����� 3 �������" << endl;
	while ((GetExitCodeThread(hTimer, &exitcode) && exitcode == STILL_ACTIVE))
	{
		arrRandomValue[2] = distribution(generator);
		Sleep(50);
	}
	return 1;
}
unsigned __stdcall thread4(void*)
{
	cout << "����� 4 �������" << endl;
	while ((GetExitCodeThread(hTimer, &exitcode) && exitcode == STILL_ACTIVE))
	{
		arrRandomValue[3] = distribution(generator);
		Sleep(50);
	}
	return 1;
}
unsigned __stdcall thread5(void*)
{
	cout << "����� 5 �������" << endl;
	while ((GetExitCodeThread(hTimer, &exitcode) && exitcode == STILL_ACTIVE))
	{
		arrRandomValue[4] = distribution(generator);
		Sleep(50);
	}
	return 1;
}

// ������ �����
unsigned __stdcall comparison(void*)
{
	cout << "����� ������� ����� �������" << endl;
	while ((GetExitCodeThread(hTimer, &exitcode) && exitcode == STILL_ACTIVE))
	{
		string count = getMaxCountEqual();
		if (count != "") cout << count << endl;
		Sleep(200);
	}
	return 1;
}
// ���������� ���������� ����� � �������
string getMaxCountEqual()
{
	// ������ ����� �������. �� �� ����� �������� � ����������, �� �� ��������� ����������
	size_t arrRandomValue_Temp[5];
	memcpy(arrRandomValue_Temp, arrRandomValue, sizeof(size_t) * 5);

	string res = "";
	string res_temp = "";
	// ���������� ���������� �����
	size_t maxCount = 1;
	size_t count = 0;

	for (size_t i = 0; i < 5; i++, count = 0, res_temp = "")
	{
		// ���������� ���������� ���������� ��� �����
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

	if (maxCount == 2) res = "���� ������:" + res;
	else if (maxCount == 3) res = "��� ������:" + res;
	else if (maxCount == 4) res = "������ ������:" + res;
	else if (maxCount == 5) res = "���� ������:" + res;

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

	// �������� ���������� ���� �������
	WaitForMultipleObjects(6, hThread, TRUE, INFINITE);

	cout << "��� ������ ��������� ������." << endl;
	system("pause");
	return 0;
}
