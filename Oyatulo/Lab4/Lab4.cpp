/*
Программа должна запускать другую программу, путь которой указан в командной строке и анализировать код ее завершения.
*/
#include <windows.h>
#include <iostream> 

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "rus");
	if (argv[1])
	{
		SHELLEXECUTEINFO ShExecInfo = { 0 };
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd = NULL;
		ShExecInfo.lpVerb = NULL;
		ShExecInfo.lpFile = argv[1];
		ShExecInfo.lpParameters = "";
		ShExecInfo.lpDirectory = NULL;
		ShExecInfo.nShow = SW_SHOW;
		ShExecInfo.hInstApp = NULL;
		ShellExecuteEx(&ShExecInfo);
		std::cout << "Ожидание завершения процесса...\n";
		WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
	}
	return 0;
}
