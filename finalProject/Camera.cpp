#include "Camera.h"
#include "Global.h"
//#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <thread>

char Camera::numOfCameras = 97;
std::mutex Camera::m;
using namespace std::literals::chrono_literals;

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
		//std::cout << "sendToBuffer camera id= " << id << '\n';
		//std::cout << "buffer  is ";
		//buffer.print();
		delete messages[i];
	}

	free(messages);
	messages = 0;
	indexMessages1 = 0;
}
void Camera::generate() {
	int count = getProb(1, 6);
	//std::cout << "generate camera id= " << id << ", count " << count << '\n';
	while (count--) {
		int id = indexMessages1 + 1;
		BaseMessage* newMessage;
		int type = getProb(1, 3);
		if (type == 1) {
			short status = getProb(1, 5);
			newMessage = new StatusMessage(id, status);
		}
		else {
			float distance = getProb(500, 10000);
			float angle = getProb(0, 360);
			float speed = getProb(0, 1000);
			newMessage = new DiscoverMessage(id, distance, angle, speed);
			//std::cout << "index is " << indexMessages1 << '\n';
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

	//send to server:
	//buffer.getBuffer();
	std::cout << "send to server id=" << id << "\n ";
	//unsigned char** prevBuffer=memcpy(prevBuffer,buffer.getBuffer(),sizeof(unsigned char**)* buffer.getNumOfMessage());
	mutexOfBuffer.lock();
	int prevSizeOfBuffer = buffer.getNumOfMessage();
	for (int i = 0; i < prevSizeOfBuffer; i++)
	{
	if (buffer.getBuffer() != NULL) {
		//std::cout << " buffer " << buffer.getBuffer();// [i] ;
		int typeOfMeassage=0;
		memcpy((void*)(&typeOfMeassage), (void*)(buffer.getBuffer()[i]), 2);
		BaseMessage* message;
		//std::cout << "typeOfMeassage; " << typeOfMeassage<<" (buffer.getBuffer():"<< buffer.getBuffer()[0] << buffer.getBuffer()[1];
		if (typeOfMeassage == 1) {
			message = new StatusMessage(buffer.getBuffer()[i], 5);
			//message = new StatusMessage(*buffer.getBuffer(), 5);
			//std::cout << "error";
		}
		else {
			message = new DiscoverMessage(buffer.getBuffer()[i], 5);
		}
		message->parseMessage();
		std::cout << "message translate:";
		message->print();
		// prevSizeOfBuffer = buffer.getNumOfMessage();
		std::cout << '\n';
	}
	
	}
buffer.cleanBuffer();
mutexOfBuffer.unlock();
	

}
bool Camera::getIsActive() {

	return isActive;
}
Camera::~Camera() {
	sendToBuffer();
}