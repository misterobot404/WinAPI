#undef UNICODE
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#define _WIN32_WINDOWS 0x0501
#define _WIN32_IE 0x0600
#include <windows.h>
#include <iostream>

void main(void)
{   //Запись нескольких команд NOP 
	BYTE ja[5] = { 0x90, 0x90, 0x90, 0x90, 0x90 };
	DWORD *p; 

//Получить доступ к адресному пространству нашего процесса
HANDLE h = OpenProcess(PROCESS_VM_OPERATION	| PROCESS_VM_WRITE,	true, GetCurrentProcessId());
	
//Получение адреса метки
_asm{
	mov p,offset m002
    }

//Записать по адресу метки четыре команды NOP (длину записи выяснили в отладчике)
WriteProcessMemory(h, p, ja, 4, NULL);

m002:goto m001;
//-----------------------------------------------------
    //Закрытая зона. Прямого доступа к этому участку кода НЕТ!
	MessageBox(0, "Вы попали в ЗАКРЫТУЮ ЗОНУ!!!", "ПРОРЫВ ЗАЩИТЫ", 0);
//----------------------------------------------------		

m001:

	system("pause");
}