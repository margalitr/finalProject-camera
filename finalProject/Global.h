#pragma once
#ifndef RANDOM
#define RANDOM
#include <mutex>
#include <sstream>
#include <WinSock2.h>
#include <WS2tcpip.h>

float getProb(int min,int max);
static std::mutex mutexConnection;
extern SOCKET connection ;
//static bool ezer = false;
//static bool* connectionWork; 
void connectToServer();

#endif // !RANDOM
