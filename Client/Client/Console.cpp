#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <cstdio>
#include <winuser.h>
#include "Socket.h"
#include "Console.h"
#pragma execution_character_set( "utf-8" )


using namespace std;
Console::Console(const int& height = 30, const int& width = 80)
{
	_width = width;
	_height = height;
	_chatText = "";
	CommandList.insert(CommandListMap::value_type("--help", EventHelp));
	CommandList.insert(CommandListMap::value_type("--users", EventUsersList));
	CommandList.insert(CommandListMap::value_type("--exit", EventExitFromChat));
	CommandList.insert(CommandListMap::value_type("--change-language", EventChangeLanguage));
	CommandList.insert(CommandListMap::value_type("--change-name", EventChangeName));
	CommandList.insert(CommandListMap::value_type("--change-channel", EventChangeChannel));
	SetConsoleTitle(TEXT("My lamp chatik"));
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_GREEN);
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.dwFontSize.X = _width;
	fontInfo.dwFontSize.Y = _height;
	fontInfo.FontWeight = 700;
	SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
};



void Console::ChangeName(const string& name)
{
	_name = name;
};
void Console::ChangeLanguage(const string& language)
{
	_language = language;
};

string Console::GetLanguage()
{
	return _language;
};

void Console::LoginInChat()
{
	cout << "Name: "; // Name
	getline(cin, _name);
	cout << "Language. Standart ISO 639-1 (ru, en, de, es, pt ...): "; // Language
	getline(cin, _language);
	while (_language != "ru" && _language != "en" && _language != "de" && _language != "es" && _language != "pt") {
		cout << endl << "Only 'ru' or 'en'" << endl;
		getline(cin, _language);
	}
	string str = _name + " logged into the chat !\n";
	Socket::SocketStart();
	Socket::SendSocketMessage(str);
	Console::Start();
};

void Console::Start()
{
	Sleep(300);
	bool enter = true;
	while (enter)
	{
		enter = false;
		getline(cin, _chatText);
		if ((_chatText[0] == '-') && (_chatText[1] == '-'))
		{
			Console::Command(_chatText);
		}
		else {
			Socket::SendSocketMessage(_name, _chatText);
		}
		enter = true;
	}
};

void Console::Command(const string& command)
{
	try
	{
		CommandList.at(command)();
	}
	catch (const std::exception& ex)
	{
		cout << "Command list: --help" << endl;
	}
};

void Console::EventHelp()
{
	cout << "--help \t\t\t Список команд" << endl;
	cout << "--users \t\t Список пользователей" << endl;
	cout << "--exit \t\t\t Выйти из чата" << endl;
	cout << "--change-language \t Поменять основной язык" << endl;
	cout << "--change-name \t\t Поменять никнейм" << endl;
	cout << "--change-channel \t Сменить канал" << endl;
};

void Console::EventUsersList() {};

void Console::EventExitFromChat() {};

void Console::EventChangeLanguage() {};

void Console::EventChangeName()
{
	string newName;
	string lastName = _name;
	cout << "--cancel для отмены действия" << endl;
	cout << "Введите новое имя: ";
	cin >> newName;
	cout << endl;
	if (newName != "--cancel")
	{
		Console::ChangeName(newName);
		string str = lastName + " изменил имя на " + newName;
		Socket::SendSocketMessage(str);
	}
};

void Console::EventChangeChannel() {};