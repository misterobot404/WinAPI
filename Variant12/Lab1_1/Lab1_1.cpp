/*
�������� �� ��������� ��������� ��� ������ � ��������� ����������� � ��������������� �������. 
��� ������� �� ������ ������ �������� �����������. � ��� ������� �� ���� � �� �� ������ ��� ���� � ������������� ���������.
*/
#include "Windows.h"

void msgShow();
int res;

size_t clickCount = 0;

size_t clickABORT = 0;
size_t clickRETRY = 0;
size_t clickIGNORE = 0;

int WINAPI WinMain
(
	HINSTANCE hInstance,	// ��������� �� ������� ���������
	HINSTANCE hPrevInstance,	// ��������� �� ���������� ���������� ���������
	LPSTR lpCmdLine,		// ��������� ������
	int nCmdShow		// ��� ����������� ���� ���������
)
{
	res = MessageBox(NULL, "��������� ��������� � ����� ��������", "���������", MB_ABORTRETRYIGNORE | MB_ICONEXCLAMATION);

	while (true)
	{
		if (res == IDABORT)
		{
			clickABORT++;
			msgShow();
		}
		else if (res == IDRETRY)
		{
			clickRETRY++;
			msgShow();
		}
		else if (res == IDIGNORE)
		{
			clickIGNORE++;
			msgShow();
		} 
		else break;	
	}
	return 0;
}

void msgShow()
{
	if (clickABORT == 2 || clickRETRY == 2 || clickIGNORE == 2)
		exit(0);

	clickCount++;

	if (clickCount == 2)
	{
		clickCount = 0;
		clickABORT = 0;
		clickRETRY = 0;
		clickIGNORE = 0;
	}

	if (clickCount == 0)
		res = MessageBox(NULL, "��������� ��������� � ����� ��������", "���������", MB_ABORTRETRYIGNORE | MB_ICONEXCLAMATION);
	else
		res = MessageBox(NULL, "��������� ��������� � ����� ��������", "���������", MB_ABORTRETRYIGNORE | MB_ICONQUESTION);
}

