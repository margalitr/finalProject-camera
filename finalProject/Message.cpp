#include "Message.h"
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
BaseMessage::BaseMessage(unsigned char* buffer, int id) {
	this->messageBuffer = buffer;
	this->messageId = id;
	messageType = static_cast<int>(buffer[1]);
}
BaseMessage::BaseMessage(int type, int id) {
	this->messageType = type;
	this->messageId = id;
	messageBuffer = 0;
}
BaseMessage::~BaseMessage() {
	//delete[] messageBuffer;
}
unsigned char*  BaseMessage::getMessageBuffer() {
	return messageBuffer;
}
StatusMessage::StatusMessage(unsigned char* buffer, int id) :BaseMessage(buffer, id) {
	status = 0;
}
StatusMessage::StatusMessage(int id, short status) :BaseMessage(1, id) {
	this->status = status;
}
 void StatusMessage::parseMessage() {
	status = static_cast<short>(messageBuffer[2]);
}
 void StatusMessage::parseBack() {
	messageBuffer = new unsigned char[3];
	memcpy((void*)(messageBuffer), (void*)(&messageType), 2);
	memcpy((void*)(messageBuffer + 2), (void*)(&status), 1);
}
 void StatusMessage::print() {
	std::cout << "status:" << status << '\n';
}
 DiscoverMessage::DiscoverMessage(unsigned char* buffer, int id) :BaseMessage(buffer, id) {
	 distance = 0;
	 angle = 0;
	 speed = 0;
 }
 DiscoverMessage::DiscoverMessage(int id, float distance, float angle, float speed) :BaseMessage(2, id) {
	 this->distance = distance;
	 this->angle = angle;
	 this->speed = speed;

 }
void  DiscoverMessage::parseMessage() {
	 memcpy((void*)(&distance), (void*)(messageBuffer + 2), 4);
	 memcpy((void*)(&angle), (void*)(messageBuffer + 6), 4);
	 memcpy((void*)(&speed), (void*)(messageBuffer + 10), 4);

 }
void  DiscoverMessage::parseBack() {
	 messageBuffer = new unsigned char[14];
	 memcpy((void*)(messageBuffer), (void*)(&messageType), 2);
	 memcpy((void*)(messageBuffer + 2), (void*)(&distance), 4);
	 memcpy((void*)(messageBuffer + 6), (void*)(&angle), 4);
	 memcpy((void*)(messageBuffer + 10), (void*)(&speed), 4);
 }
 void  DiscoverMessage::print() {
	 std::cout << "distance:" << distance << " angle:" << angle << " speed:" << speed << '\n';
 }