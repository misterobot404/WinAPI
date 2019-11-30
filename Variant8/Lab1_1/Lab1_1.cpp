/*
Поместить на выводимом сообщении три кнопки «ДА», «НЕТ», «Отмена». 
При нажатии на кнопку «ДА» должен меняться основной текст сообщения. 
При нажатии на кнопку «НЕТ» - должен меняться текст заголовка окна сообщения, при нажатии на «Отмена» - заканчивается работа программы.
*/

#include <windows.h>
#include <string>
using namespace std;

int WINAPI WinMain
(
	_In_ HINSTANCE,	// дескриптор экземпляра приложения. Этот дескриптор содержит адрес начала кода программы в ее адресном пространстве. Дескриптор hInstance чаще всего требуется функциям, работающим с ресурсами программы.
	_In_opt_ HINSTANCE,	// дескриптор предыдущего экземпляра приложения. Этот дескриптор остался от старых версий Windows - скорее всего, вам он никогда не пригодится. Всегда равен 0.
	_In_ LPSTR,		// указатель на начало командной строки, введенной при запуске программы.
	_In_ int		// это значение содержит желаемый вид окна (например, свернутый или развернутый).
)
{
	int headerNumber = 0;
	int textNumber = 0;
	string header = "Заголовок окна";
	string text = "Текст сообщения";

	int msgRes = MessageBox(0, text.c_str(), header.c_str(), MB_YESNOCANCEL);
	while (true)
	{
		switch (msgRes)
		{
		case IDYES:
			text = "Текст сообщения " + to_string(++textNumber);
			msgRes = MessageBox(0, text.c_str(), header.c_str(), MB_YESNOCANCEL);
			break;
		case IDNO:
			header = "Заголовок окна " + to_string(++headerNumber);
			msgRes = MessageBox(0, text.c_str(), header.c_str(), MB_YESNOCANCEL);
			break;
		case IDCANCEL:
			return 0;
		}
	}
}


