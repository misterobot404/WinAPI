/*
���� ����� ������ ����, ��������� � ������ ��������� ���������, ������ ����� ������ ����, ��������� �� ������ ��������� ���������.
������ ����� ���������� ����� � ������� �� ����� ������ � �������� ������������� ������.
*/

#include <iostream>
#include <windows.h>
#include <process.h>
#include <fstream>
#include <cstdlib>
using namespace std;

////// GLOBAL VARIABLE //////
// ������� ���������� ���������� � ������� ������
HANDLE hEventRead[2], hEvent�omparison[2];
// ����r� ��� ������ ������ �� ������
ifstream filestream1;
ifstream filestream2;
// �������� ������������ ����� �� ������� � ������� ������
char byte1;
char byte2;
// ��������� ��������� ������
bool filestream1Compl;
bool filestream2Compl;
// ��������� ��������� ���������
bool comparisonCompl;
///////////////////////////

// ���������� ������ ������� �����
unsigned __stdcall read1(void* stream)
{
	filestream1Compl = false;
	while (!comparisonCompl)
	{
		// ����� comparison �������� ��������� ������, ��������� ������
		WaitForSingleObject(hEvent�omparison[0], INFINITE);

		if (!filestream1.get(byte1)) filestream1Compl = true;

		// ������������� � ���������� ���������� �����
		SetEvent(hEventRead[0]);
	}
	return 0;
}

// ���������� ������ ������� �����
unsigned __stdcall read2(void* stream)
{
	filestream2Compl = false;
	while (!comparisonCompl)
	{
		WaitForSingleObject(hEvent�omparison[1], INFINITE);
		if (!filestream2.get(byte2)) filestream2Compl = true;
		SetEvent(hEventRead[1]);
	}
	return 0;
}

// ��������� ������
unsigned __stdcall comparison(void*)
{
	// �������� ������ ������������� �����
	size_t indexByte = 0;

	comparisonCompl = false;

	while (!comparisonCompl)
	{
		// ������ �������� TRUE, ���� ����� ����� ������������ ���� �������, FALSE ���� ������ ������� �� �������
		WaitForMultipleObjects(2, hEventRead, TRUE, INFINITE);

		// ���� ������ ����� � ������ ����� ��������� ������ �������
		if (filestream1Compl == true && filestream2Compl == true)
		{
			comparisonCompl = true;
			// ��� ������� ������ �������� ��� �� ����� ����������������
			SetEvent(hEvent�omparison[0]);
			SetEvent(hEvent�omparison[1]);
			break;
			
		}

		++indexByte;
		if (byte1 != byte2)
		{
			cout << "*������� ������������*" << endl;
			cout << "����� �� ������������ �����: " << indexByte << endl;

			cout << "���� �� ������� ����� (� ���� HEX): ";
			if (filestream1Compl) cout << "�����������";
			else cout << hex << (int)byte1 << " (" << byte1 << ")";
			cout << endl;

			cout << "���� �� ������� ����� (� ���� HEX): ";
			if (filestream2Compl) cout << "�����������";
			else cout << hex << (int)byte2 << " (" << byte2 << ")";
			cout << endl << endl;
		}
		
		// ��� ������� ������ �������� ��� �� ����� ����������������
		SetEvent(hEvent�omparison[0]);
		SetEvent(hEvent�omparison[1]);
	}
	return 0;
}

int	main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	system("color 0A");

	// ���� �������� ���������, �� argc ����� ������ 1 (� ����������� �� ���-�� ����������)
	if (argc != 3)
	{
		cout << "��� ������� ��������� ��������� ��� ���������: ���� �� ������� � ������� �����." << endl;
		system("pause");
		return -1;
	}

	cout << "����������: ��� ���������� ������ ��������� ������������ ����� ������ ���� � ��������� Windows-1251 (��� ������ ������������ ���������)." << endl << endl;

	// �������� ����� �� ����� �� ����������
	filestream1.open(argv[1], ios::binary);
	filestream2.open(argv[2], ios::binary);

	// �������� �������� �������
	if (filestream1 && filestream2)
	{
		// ������������� �������
		// 2 ���: ��� ������ ������� false - ������, true - ����
		// 3 ���: ��������� ��������� �������
		hEventRead[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
		hEventRead[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
		hEvent�omparison[0] = CreateEvent(NULL, FALSE, TRUE, NULL);
		hEvent�omparison[1] = CreateEvent(NULL, FALSE, TRUE, NULL);

		HANDLE hThread[3];
		// ������ ����������
		// ������� ������� ����� �� ������ � ������ ����
		hThread[0] = (HANDLE)_beginthreadex(NULL, 0, &read1, &filestream1, 0, NULL);
		hThread[1] = (HANDLE)_beginthreadex(NULL, 0, &read2, &filestream2, 0, NULL);
		// ����� ���������
		hThread[2] = (HANDLE)_beginthreadex(NULL, 0, &comparison, NULL, 0, NULL);

		// �������� ���������� ���� �������
		WaitForMultipleObjects(3, hThread, TRUE, INFINITE);
		cout << "��� ������ ��������� ������." << endl;
		filestream1.close();
		filestream2.close();
	}
	else cout << "������ �������� ������!" << endl;

	system("pause");
	return 0;
}
