#include "Camera.h"
#include "Random.h"
//#include <stdlib.h>
#include <stdio.h>
#include <iostream>
char Camera::numOfCameras =1;
Camera::Camera() {
	id = Camera::numOfCameras;
	numOfCameras++;
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
	for (int i = 0; i < indexMessages; i++)
	{
		messages[i]->parseBack();
		buffer.addToBuffer(messages[i]->getMessageBuffer());
		std::cout << "sendToBuffer camera id= " << id << '\n';
		std::cout << "buffer  is ";
		buffer.print();
		delete messages[i];
	}

	 free(messages);
	 messages = 0;
	 indexMessages = 0;
}
void Camera::generate() {
	int count = getProb(1, 6);
	std::cout << "generate camera id= " << id <<", count "<<count<< '\n';
	while (count--) {
		int id= indexMessages+1;
		float distance= getProb(500, 10000);
		float angle= getProb(0 ,360);
		float speed= getProb(0 , 1000); 
		BaseMessage* newMessage = new DiscoverMessage(id, distance, angle, speed);
		std::cout << "index is " << indexMessages << '\n';
		BaseMessage** tmpMassages =  (BaseMessage**)realloc(messages,sizeof(BaseMessage*)*(indexMessages+1));
		int cnt = 0;
		while (tmpMassages==NULL) {
			sendToBuffer();
			 tmpMassages = (BaseMessage**)realloc(messages, sizeof(BaseMessage*) * (indexMessages + 1));
			if (cnt++ == 3) {
				std::cout << "I didn't have place of memory, sory!" << '\n';
				stop();
			}
		}
		messages = tmpMassages;
		messages[indexMessages] = newMessage;
		std::cout << " messages is " ;
		messages[indexMessages]->print();
		indexMessages++;
	}
}
void Camera::sendToServer() {
	//send to server:
	buffer.getBuffer();
	std::cout << "send to buffer: "  << '\n';

	for (int i = 0; i < buffer.getNumOfMessage(); i++)
	{
		std::cout<<"buffer: "<<buffer.getBuffer()[i] << '\n';
	}
}
bool Camera::getIsActive() {

	return isActive;
}
Camera::~Camera() {
	sendToBuffer();

}