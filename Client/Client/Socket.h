#pragma once
#include <string>
using namespace std;

class Socket
{
public:
    Socket();
    static void SendMessage(string message);
    static void SendMessage(string name, string message);

private:
    int _port;
    string _addr;
    static void ClientHandler();
    static void SendMessageToServer(string message);
};
