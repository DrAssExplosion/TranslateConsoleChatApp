#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include "Socket.h"
#include "Console.h"
#pragma warning(disable : 4996)
using namespace std;

SOCKET Connection;

Socket::Socket()
{
    Socket::_port = 1111;
    Socket::_addr = "127.0.0.1";
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0)
    {
        cout << "Error" << endl;
        exit(1);
    }
    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr(Socket::_addr.c_str());
    addr.sin_port = htons(Socket::_port);
    addr.sin_family = AF_INET;

    Connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
    {
        cout << "Error: failed connect to server.\n";
    }
    cout << "Соединение установлено !\n";
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Socket::ClientHandler, NULL, 0, NULL);

    Console(50, 50); // Конструктор окна консоли
    Console::LoginInChat(); // Авторизация
    Console::Start();
};

void Socket::SendMessage(string message)
{
    string str = message;
    SendMessageToServer(str);
};

void Socket::SendMessage(string name, string message)
{
    string str = name + ": " + message;
    SendMessageToServer(str);
};

void Socket::SendMessageToServer(string message)
{
    int message_size = message.size();
    send(Connection, (char*)&message_size, sizeof(int), 0);    // Отправляем размер строки серверу
    send(Connection, message.c_str(), message_size, 0); // Отправляем строку серверу
};

void Socket::ClientHandler()
{
    int message_size;
    while (true)
    {
        recv(Connection, (char*)&message_size, sizeof(int), 0); // Принимаем размер сообщения
        char* message = new char[message_size + 1];
        message[message_size] = '\0';
        recv(Connection, message, message_size, 0); // Принимаем сообщение
        cout << message << endl;                    // Выводим сообщение
        delete[] message;
    }
};
