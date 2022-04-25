#include "Camera.h"
#include "Random.h"
#include <stdlib.h>
#include <stdio.h>

Camera::Camera() {

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
	}
	 free(messages);
	 messages = 0;
}
void Camera::generate() {
	int count = getProb(1, 6);
	while (count--) {
		int id= indexMessages+1;
		float distance= getProb(500, 10000);
		float angle= getProb(0 ,360);
		float speed= getProb(0 , 1000);
		messages[indexMessages++] = new DiscoverMessage(id, distance, angle, speed);
	}
}