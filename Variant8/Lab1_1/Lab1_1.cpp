/*
��������� �� ��������� ��������� ��� ������ ����, ���һ, �������. 
��� ������� �� ������ ���� ������ �������� �������� ����� ���������. 
��� ������� �� ������ ���һ - ������ �������� ����� ��������� ���� ���������, ��� ������� �� ������� - ������������� ������ ���������.
*/

#include <windows.h>
#include <string>
using namespace std;

int WINAPI WinMain
(
	_In_ HINSTANCE,	// ���������� ���������� ����������. ���� ���������� �������� ����� ������ ���� ��������� � �� �������� ������������. ���������� hInstance ���� ����� ��������� ��������, ���������� � ��������� ���������.
	_In_opt_ HINSTANCE,	// ���������� ����������� ���������� ����������. ���� ���������� ������� �� ������ ������ Windows - ������ �����, ��� �� ������� �� ����������. ������ ����� 0.
	_In_ LPSTR,		// ��������� �� ������ ��������� ������, ��������� ��� ������� ���������.
	_In_ int		// ��� �������� �������� �������� ��� ���� (��������, ��������� ��� �����������).
)
{
	int headerNumber = 0;
	int textNumber = 0;
	string header = "��������� ����";
	string text = "����� ���������";

	int msgRes = MessageBox(0, text.c_str(), header.c_str(), MB_YESNOCANCEL);
	while (true)
	{
		switch (msgRes)
		{
		case IDYES:
			text = "����� ��������� " + to_string(++textNumber);
			msgRes = MessageBox(0, text.c_str(), header.c_str(), MB_YESNOCANCEL);
			break;
		case IDNO:
			header = "��������� ���� " + to_string(++headerNumber);
			msgRes = MessageBox(0, text.c_str(), header.c_str(), MB_YESNOCANCEL);
			break;
		case IDCANCEL:
			return 0;
		}
	}
}


