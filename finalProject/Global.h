#pragma once
#ifndef RANDOM
#define RANDOM
#include <mutex>
#include <sstream>
#include <WinSock2.h>
#include <WS2tcpip.h>

float getProb(int min,int max);
extern SOCKET connection ;
void connectToServer();

#endif // !RANDOM
