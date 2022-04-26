#include <stdio.h>
#include <stdlib.h>
#include "Buffer.h"
#include <iostream>


Buffer::~Buffer() {
	cleanBuffer();

}
void Buffer::addToBuffer(unsigned char* newBuffer) {
	m.lock();
	buffer = (unsigned char**)realloc(buffer, ++i * sizeof(unsigned char*));
	if (!buffer) {
		m.unlock();
		return;
	}
	buffer[i - 1] = newBuffer;
	m.unlock();
}
unsigned char** Buffer::getBuffer() {

	return buffer;

}
void Buffer::cleanBuffer() {
	std::cout << "----------------------i= " << i << '\n';

	for (int j = 0; j < i; j++)
	{
		delete[] buffer[j];
		std::cout << "----------------------free" << '\n';
	}
	i = 0;
	free(buffer);

	buffer = (unsigned char**)malloc(sizeof(unsigned char*));
	//buffer = (unsigned char**)realloc(buffer, sizeof(unsigned char*));

}
Buffer::Buffer() {
	buffer = (unsigned char**)malloc(sizeof(char*));

}
int Buffer::getNumOfMessage() {
	return i;
}
void  Buffer::print() {
	for (int j = 0; j < i; j++)
	{
		std::cout << "buffer[" << i << "] is ";
		m.lock();
		unsigned char* tmp = buffer[i];
		while (tmp) {
			std::cout << *tmp;
			tmp++;
		}
		m.unlock();
		std::cout << '\n';
	}

}
