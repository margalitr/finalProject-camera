#include <stdio.h>
#include <stdlib.h>
#include "Buffer.h"
#include <iostream>
#include "Global.h"


Buffer::~Buffer() {
	cleanBuffer();

}
void Buffer::addToBuffer(unsigned char* newBuffer) {
	mutexOfBuffer.lock();
	notEmptyBuffer = true;
	buffer = (unsigned char**)realloc(buffer, ++i * sizeof(unsigned char*));
	if (!buffer) {
		mutexOfBuffer.unlock();
		return;
	}
	buffer[i - 1] = newBuffer;
	mutexOfBuffer.unlock();
}
unsigned char** Buffer::getBuffer() {
	//mutexOfBuffer.lock();
	if (!notEmptyBuffer)
		return NULL;
	//unsigned char** bufferNow= buffer;
	//mutexOfBuffer.unlock();
	return buffer;
}
void Buffer::cleanBuffer() {

	mutexOfBuffer.lock();
	notEmptyBuffer = false;

	//std::cout << "----------------------i= " << i << '\n';

	for (int j = 0; j < i; j++)
	{
		delete[] buffer[j];
		//std::cout << "----------------------free" << '\n';
	}
	i = 0;
	free(buffer);

	buffer = (unsigned char**)malloc(sizeof(unsigned char*));
	mutexOfBuffer.unlock();

	//buffer = (unsigned char**)realloc(buffer, sizeof(unsigned char*));

}
Buffer::Buffer() {
	mutexOfBuffer.lock();

	buffer = (unsigned char**)malloc(sizeof(char*));
	mutexOfBuffer.unlock();

}
int Buffer::getNumOfMessage() {
	return i;
}
void  Buffer::print() {
	//for (int j = 0; j < i; j++)
	//{
	//	//std::cout << "buffer[" << i << "] is ";
	//	m.lock();
	//	/*unsigned char* tmp = buffer[i];
	//	while (tmp) {
	//		std::cout << *tmp;
	//		tmp++;
	//	}*/
	//	m.unlock();
	//	std::cout << '\n';
	//}

}
