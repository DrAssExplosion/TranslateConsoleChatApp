#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <cstdio>

#include <iomanip>
#include <ranges>
#include <string_view>
#include <numeric>
#include <iterator>
#include <algorithm>

#include "Socket.h"
#include "Console.h"
#include "TranslateText.h"
#pragma warning(disable : 4996)
#pragma execution_character_set( "utf-8" )
using namespace std;

SOCKET Connection;

void Socket::SocketStart()
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
	cout << "The connection is established !\n";
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Socket::ClientHandler, NULL, 0, NULL);
};

void Socket::SendSocketMessage(string message)
{
	SendMessageToServer(message);
};

void Socket::SendSocketMessage(string name, string message)
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
		char* msg = new char[message_size + 1];
		msg[message_size] = '\0';
		recv(Connection, msg, message_size, 0); // Принимаем сообщение
		string msgString = msg;
		size_t iterFind = msgString.find(':');
		string userName, message;
		if (iterFind != string::npos) {
			if (iterFind + 2 < msgString.length()) {
				move(begin(msgString), begin(msgString) + iterFind + 1, back_inserter(userName)); // Name:
				move(begin(msgString) + iterFind + 1, end(msgString), back_inserter(message)); // Message
				cout << userName << TranslateText::Translate(message) << endl; // Выводим сообщение
			}
		}
		else {
			cout << msgString << endl;
		}
		delete[] msg;
	}
};
