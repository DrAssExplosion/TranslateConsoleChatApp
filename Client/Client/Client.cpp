#include <iostream>
#include <Windows.h>
#include <locale>

#include "Socket.h"
#include "Json.h"
#include "Console.h"
#include "TranslateText.h"
#pragma execution_character_set( "utf-8" )
using namespace std;



int main(int argc, char* argv[])
{
	SetConsoleOutputCP(CP_UTF8),
	// SetConsoleCP(CP_UTF8);
	SetConsoleCP(1251);
	Console(50, 50); // Конструктор окна консоли
	Console::_accessToken = ""; // Example - "t1.9euelZrNzs-KkovPyc2Jxsa...";
	Console::_folderIdTranslate = ""; // Example - "b1gc2r...";
    Console::LoginInChat();


	system("pause");
	return 0;
}