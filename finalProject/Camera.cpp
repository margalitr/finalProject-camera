#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "Ws2_32.lib")
#include <iostream>
#include <string.h>
#include <sstream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include "Camera.h"
#include "Global.h"
using namespace std;

char Camera::numOfCameras = 97;
std::mutex Camera::m;
using namespace std::literals::chrono_literals;
void sending(unsigned char* buffer, int* typeOfMeassage);

Camera::Camera() {
	m.lock();
	id = Camera::numOfCameras;
	Camera::numOfCameras++;
	m.unlock();
	isActive = true;
	std::cout << "Camera::numOfCameras  " << Camera::numOfCameras;
	indexMessages1 = 0;
	messages = (BaseMessage**)malloc(sizeof(BaseMessage*));
}

void Camera::stop() {
	isActive = false;
}

void Camera::run() {
	while (isActive) {
		generate();
		if (isActive) {
			sendToBuffer();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Camera::sendToBuffer() {
	for (int i = 0; i < indexMessages1; i++)
	{
		messages[i]->parseBack();
		buffer.addToBuffer(messages[i]->getMessageBuffer());
		delete messages[i];
	}
	free(messages);
	messages = 0;
	indexMessages1 = 0;
}

void Camera::generate() {
	int count = getProb(1, 6);
	while (count--) {
		int id = indexMessages1 + 1;
		BaseMessage* newMessage;
		int type = getProb(1, 3);
		if (type == 1) {
			short status = getProb(1, 3);
			newMessage = new StatusMessage(id, status);
		}
		else {
			float distance = getProb(500, 10000);
			float angle = getProb(0, 360);
			float speed = getProb(0, 1000);
			newMessage = new DiscoverMessage(id, distance, angle, speed);
		}
		BaseMessage** tmpMassages = (BaseMessage**)realloc(messages, sizeof(BaseMessage*) * (indexMessages1 + 1));
		int cnt = 0;
		while (tmpMassages == NULL) {
			sendToBuffer();
			tmpMassages = (BaseMessage**)realloc(messages, sizeof(BaseMessage*) * (indexMessages1 + 1));
			if (cnt++ == 3) {
				if (cnt++ == 3) {
					std::cout << "I didn't have place of memory, sory!" << '\n';
					stop();
					return;
				}
			}
		}
		messages = tmpMassages;
		messages[indexMessages1] = newMessage;
		std::cout << "generate messages is ";
		messages[indexMessages1]->print();
		indexMessages1++;
	}
}


void Camera::sendToServer() {
	buffer.mutexOfBuffer.lock();
	int prevSizeOfBuffer = buffer.getNumOfMessage();
	for (int i = 0; i < prevSizeOfBuffer; i++)
	{
		if (buffer.getBuffer() != NULL) {
			int typeOfMeassage = 0;
			memcpy((void*)(&typeOfMeassage), (void*)(buffer.getBuffer()[i]), 2);
			if (buffer.getBuffer()[i]) {
				sending(buffer.getBuffer()[i], &typeOfMeassage);
			}
			BaseMessage* message;
			if (typeOfMeassage == 1) {
				message = new StatusMessage(buffer.getBuffer()[i], 5);
			}
			else {
				message = new DiscoverMessage(buffer.getBuffer()[i], 5);
			}
			message->parseMessage();
			std::cout << "message translate:";
			message->print();
			std::cout << '\n';
		}
	}
	buffer.cleanBuffer();
	buffer.mutexOfBuffer.unlock();
}

bool Camera::getIsActive() {
	return isActive;
}

Camera::~Camera() {
	sendToBuffer();
}

void sending(unsigned char* buffer, int* typeOfMeassage)
{
	int size;
	if (*typeOfMeassage == 1) {
		size = 3;
	}
	else
		size = 14;
	send(connection, reinterpret_cast<char*>(buffer), size, 0);
}