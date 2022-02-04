#pragma once
#include <string>
#include <map>
using namespace std;

typedef map<string, void (*)()> CommandListMap;

class Console
{
private:
    int _width, _height;
    inline static string _name, _language, _chatText;
    inline static CommandListMap CommandList;
    static void EventHelp();
    static void EventUsersList();
    static void EventExitFromChat();
    static void EventChangeLanguage();
    static void EventChangeName();
    static void EventChangeChannel();

public:
    Console(const int& height, const int& width);
    static void ChangeName(const string& name);
    static void ChangeLanguage(const string& language);
    static void LoginInChat();
    static void Start();
    static void Command(const string& command);
};
