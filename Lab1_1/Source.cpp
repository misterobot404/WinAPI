#include "Windows.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	int Ret = MessageBox(0, "�� �������?", "���. �����", MB_YESNOCANCEL| MB_ICONINFORMATION);

	while (true)
	{
		switch (Ret)
		{
		case IDYES:
			MessageBox(0, "����������", "���. �����", MB_OK);
			exit(0);
		case IDNO:
			Ret = MessageBox(0, "�� �������?", "���. �����", MB_YESNOCANCEL | MB_ICONEXCLAMATION);
			break;
		case IDCANCEL:
			exit(0);
		}
	}
}