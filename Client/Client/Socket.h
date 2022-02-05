#pragma once
#include <string>
using namespace std;

class Socket
{
public:
    static void SocketStart();
    static void SendSocketMessage(string message);
    static void SendSocketMessage(string name, string message);

private:
    inline static int _port;
    inline static string _addr;
    static void ClientHandler();
    static void SendMessageToServer(string message);
};
