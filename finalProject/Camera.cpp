#include "Camera.h"
#include "Global.h"
//#include <stdlib.h>
#include <stdio.h>
#include <iostream>

char Camera::numOfCameras = 97;
std::mutex Camera::m;

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
		float distance = getProb(500, 10000);
		float angle = getProb(0, 360);
		float speed = getProb(0, 1000);
		BaseMessage* newMessage = new DiscoverMessage(id, distance, angle, speed);
		//std::cout << "index is " << indexMessages1 << '\n';
		BaseMessage** tmpMassages = (BaseMessage**)realloc(messages, sizeof(BaseMessage*) * (indexMessages1 + 1));
		int cnt = 0;
		while (tmpMassages == NULL) {
			sendToBuffer();
			tmpMassages = (BaseMessage**)realloc(messages, sizeof(BaseMessage*) * (indexMessages1 + 1));
			if (cnt++ == 3) {
				std::cout << "I didn't have place of memory, sory!" << '\n';
				stop();
			}
		}
		messages = tmpMassages;
		messages[indexMessages1] = newMessage;
		//std::cout << " messages is " ;
		//messages[indexMessages1]->print();
		indexMessages1++;
	}
}
void Camera::sendToServer() {

	//send to server:
	buffer.getBuffer();
	std::cout << "send to server \n buffer: ";
	//unsigned char** prevBuffer=memcpy(prevBuffer,buffer.getBuffer(),sizeof(unsigned char**)* buffer.getNumOfMessage());
	mutexOfBuffer.lock();
	int prevSizeOfBuffer = buffer.getNumOfMessage();
	mutexOfBuffer.unlock();
	//for (int i = 0; i < prevSizeOfBuffer-1; i++)
	//{
		mutexOfBuffer.lock();
		std::cout <<" buffer " << buffer.getBuffer();// [i] ;
		// prevSizeOfBuffer = buffer.getNumOfMessage();
		mutexOfBuffer.unlock();

	//}
	std::cout << '\n';
	

	buffer.cleanBuffer();

}
bool Camera::getIsActive() {

	return isActive;
}
Camera::~Camera() {
	sendToBuffer();
}