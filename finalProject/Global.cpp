#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Global.h"
#include <iostream>
#include <random>
#include <string.h>
#include <sstream>
#include <WinSock2.h>
#include <WS2tcpip.h>
using namespace std;
SOCKET connection;
//connection = socket(AF_INET, SOCK_STREAM, NULL);
float getProb(int min, int max) {
	std::random_device rd;
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
	std::mt19937 mt{ ss };
	std::uniform_real_distribution<float>  _dist(min, max+1);

	return _dist(mt);
}

void connectToServer() {
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) {
		cout << "Winsock Connection Failed!" << endl;
	}
	SOCKADDR_IN addr;
	int addrLen = sizeof(addr);
	IN_ADDR ipvalue;
	//connection = socket(AF_INET, SOCK_STREAM, NULL);
	//InetPton(AF_INET,"127.0.0.1", &addr.sin_addr.s_addr);
	//InetPton(,"127.0.0.1",addr.sin_addr.s_addr)
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(80);
	addr.sin_family = AF_INET;
	connection = socket(AF_INET, SOCK_STREAM, NULL);
	//mutexConnection.lock();
	//bool ezer = true;
	//connectionWork = &ezer;
	//mutexConnection.unlock();

	if (connect(connection, (SOCKADDR*)&addr, addrLen) == 0) {
		cout << "Connected!" << endl;
	}
	else {
		cout << "Error Connecting to Host" << endl;
		exit(1);
	}
}