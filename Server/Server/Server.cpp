#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <cstdio>
#pragma execution_character_set( "utf-8" )
#pragma warning(disable : 4996)
using namespace std;

SOCKET Connections[100];
int Counter = 0;

void ClientHandler(int index)
{
	int message_size;
	while (true)
	{
		recv(Connections[index], (char*)&message_size, sizeof(int), 0);
		char* message = new char[message_size + 1];
		message[message_size] = '\0';
		recv(Connections[index], message, message_size, 0);
		cout << "message_size - " << message_size << endl;
		for (int i = 0; i < Counter; i++)
		{
			/*if (i == index)
			{
				continue;
			}*/
			send(Connections[i], (char*)&message_size, sizeof(int), 0);
			send(Connections[i], message, message_size, 0);
		}
		delete[] message;
	};
};

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	//SetConsoleCP(65001);
	//SetConsoleOutputCP(65001);
	// WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	for (int i = 0; i < 100; i++)
	{
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		if (newConnection == 0)
		{
			cout << "Error #2\n";
		}
		else
		{
			Connections[i] = newConnection;
			Counter++;
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), 0, NULL);
		}
	}

	system("pause");
	return 0;
}