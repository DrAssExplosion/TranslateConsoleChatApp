#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <winuser.h>
#include "Socket.h"
#include "Console.h"

using namespace std;
Console::Console(const int& height = 50, const int& width = 50)
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
    SetConsoleTitle(LPCTSTR("My lamp chatik"));                             // Уѝтановить заголовок
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                      // Получить конѝоль
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_GREEN); // Уѝтановить ѝтиль текѝта
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.dwFontSize.X = _width;                     // Размер (в логичеѝких единицах)
    fontInfo.dwFontSize.Y = _height;                    // Размер (в логичеѝких единицах)
    fontInfo.FontWeight = 700;                          // Размер (в логичеѝких единицах)
    SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo); // Уѝтановить ѝтиль текѝта
    LoginInChat();                                      // Подключение к чату
    Start();                                            // Начало ѝеѝѝии
};



void Console::ChangeName(const string& name)
{
    _name = name;
};
void Console::ChangeLanguage(const string& language)
{
    _language = language;
};

void Console::LoginInChat()
{
    cout << "���: "; // Name
    cin >> _name;
    cout << "����. ����������� � ������� ISO 639-1 (ru, en, ...): "; // Language
    cin >> _language;
    string str = _name + " ����� � ��� !\n";
    Socket::SendMessage(str);
};

void Console::Start()
{
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
            Socket::SendMessage(_name, _chatText);
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
    cout << "--help \t\t\t ������ ������" << endl;
    cout << "--users \t\t ������ �������������" << endl;
    cout << "--exit \t\t\t ����� �� ����" << endl;
    cout << "--change-language \t �������� �������� ����" << endl;
    cout << "--change-name \t\t �������� �������" << endl;
    cout << "--change-channel \t ������� �����" << endl;
};

void Console::EventUsersList() {};

void Console::EventExitFromChat() {};

void Console::EventChangeLanguage() {};

void Console::EventChangeName()
{
    string newName;
    string lastName = _name;
    cout << "--cancel ��� ������ ��������" << endl;
    cout << "������� ����� ���: ";
    cin >> newName;
    cout << endl;
    if (newName != "--cancel")
    {
        Console::ChangeName(newName);
        string str = lastName + " ������� ��� �� " + newName;
        Socket::SendMessage(str);
    }
};

void Console::EventChangeChannel() {};