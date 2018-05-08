#pragma once
#include<WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include<conio.h>
#include<stdio.h>

// Include the Winsock library (lib) file
#pragma comment (lib, "ws2_32.lib")

using namespace std;
//client side UDP code
class sendData
{
public:
	boolean DataSend(char data_send[64])
	{
		////////////////////////////////////////////////////////////
		// INITIALIZE WINSOCK
		////////////////////////////////////////////////////////////

		// Structure to store the WinSock version. This is filled in
		// on the call to WSAStartup()
		WSADATA data;

		// To start WinSock, the required version must be passed to
		// WSAStartup(). This server is going to use WinSock version
		// 2 so I create a word that will store 2 and 2 in hex i.e.
		// 0x0202
		WORD version = MAKEWORD(2, 2);

		// Start WinSock
		int wsOk = WSAStartup(version, &data);
		if (wsOk != 0)
		{
			// Not ok! Get out quickly
			cout << "Can't start Winsock! " << wsOk;
			return false;
		}

		////////////////////////////////////////////////////////////
		// CONNECT TO THE SERVER
		////////////////////////////////////////////////////////////

		// Create a hint structure for the server
		sockaddr_in server;
		server.sin_family = AF_INET; // AF_INET = IPv4 addresses
		server.sin_port = htons(6045); // Little to big endian conversion
		inet_pton(AF_INET, "172.31.1.154", &server.sin_addr); // Convert from string to byte array

															  // Socket creation, note that the socket type is datagram
		SOCKET out = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		
		fflush(stdin);
		int sendOk = sendto(out, data_send, 80, 0, (sockaddr*)&server, sizeof(server));
		printf("%s", data_send);
		if (sendOk == SOCKET_ERROR)
		{
			cout << "That didn't work! " << WSAGetLastError() << endl;
			return false;
		}
		fflush(stdin);

		// Close the socket
		closesocket(out);

		// Close down Winsock
		WSACleanup();
		return true;
	}
};




