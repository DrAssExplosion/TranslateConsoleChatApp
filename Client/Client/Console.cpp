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
    SetConsoleTitle(LPCTSTR("My lamp chatik"));                             // –£—ù—Ç–∞–Ω–æ–≤–∏—Ç—å –∑–∞–≥–æ–ª–æ–≤–æ–∫
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                      // –ü–æ–ª—É—á–∏—Ç—å –∫–æ–Ω—ù–æ–ª—å
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_GREEN); // –£—ù—Ç–∞–Ω–æ–≤–∏—Ç—å —ù—Ç–∏–ª—å —Ç–µ–∫—ù—Ç–∞
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.dwFontSize.X = _width;                     // –†–∞–∑–º–µ—Ä (–≤ –ª–æ–≥–∏—á–µ—ù–∫–∏—Ö –µ–¥–∏–Ω–∏—Ü–∞—Ö)
    fontInfo.dwFontSize.Y = _height;                    // –†–∞–∑–º–µ—Ä (–≤ –ª–æ–≥–∏—á–µ—ù–∫–∏—Ö –µ–¥–∏–Ω–∏—Ü–∞—Ö)
    fontInfo.FontWeight = 700;                          // –†–∞–∑–º–µ—Ä (–≤ –ª–æ–≥–∏—á–µ—ù–∫–∏—Ö –µ–¥–∏–Ω–∏—Ü–∞—Ö)
    SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo); // –£—ù—Ç–∞–Ω–æ–≤–∏—Ç—å —ù—Ç–∏–ª—å —Ç–µ–∫—ù—Ç–∞
    LoginInChat();                                      // –ü–æ–¥–∫–ª—é—á–µ–Ω–∏–µ –∫ —á–∞—Ç—É
    Start();                                            // –ù–∞—á–∞–ª–æ —ù–µ—ù—ù–∏–∏
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
    cout << "»Ïˇ: "; // Name
    cin >> _name;
    cout << "ﬂÁ˚Í. ”Í‡Á˚‚‡ÂÚÒˇ ‚ ÙÓÏ‡ÚÂ ISO 639-1 (ru, en, ...): "; // Language
    cin >> _language;
    string str = _name + " ‚Ó¯∏Î ‚ ˜‡Ú !\n";
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
    cout << "--help \t\t\t —ÔËÒÓÍ ÍÓÏ‡Ì‰" << endl;
    cout << "--users \t\t —ÔËÒÓÍ ÔÓÎ¸ÁÓ‚‡ÚÂÎÂÈ" << endl;
    cout << "--exit \t\t\t ¬˚ÈÚË ËÁ ˜‡Ú‡" << endl;
    cout << "--change-language \t œÓÏÂÌˇÚ¸ ÓÒÌÓ‚ÌÓÈ ˇÁ˚Í" << endl;
    cout << "--change-name \t\t œÓÏÂÌˇÚ¸ ÌËÍÌÂÈÏ" << endl;
    cout << "--change-channel \t —ÏÂÌËÚ¸ Í‡Ì‡Î" << endl;
};

void Console::EventUsersList() {};

void Console::EventExitFromChat() {};

void Console::EventChangeLanguage() {};

void Console::EventChangeName()
{
    string newName;
    string lastName = _name;
    cout << "--cancel ‰Îˇ ÓÚÏÂÌ˚ ‰ÂÈÒÚ‚Ëˇ" << endl;
    cout << "¬‚Â‰ËÚÂ ÌÓ‚ÓÂ ËÏˇ: ";
    cin >> newName;
    cout << endl;
    if (newName != "--cancel")
    {
        Console::ChangeName(newName);
        string str = lastName + " ËÁÏÂÌËÎ ËÏˇ Ì‡ " + newName;
        Socket::SendMessage(str);
    }
};

void Console::EventChangeChannel() {};