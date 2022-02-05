#include <iostream>
#include <string>

#include "Socket.h"
#include "Json.h"
#include "Console.h"
#include "TranslateText.h"
#pragma execution_character_set( "utf-8" )
using namespace std;



int main(int argc, char* argv[])
{
	Console(50, 50); // Конструктор окна консоли
	Console::_accessToken = "";
	Console::_folderIdTranslate = "";
	Console::LoginInChat();
	//Socket();

	system("pause");
	return 0;
}