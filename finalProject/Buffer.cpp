#include <stdio.h>
#include <stdlib.h>
#include "Buffer.h"
#include <iostream>
#include "Global.h"

Buffer::~Buffer() {
	cleanBuffer();
	free(buffer);
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
	if (!notEmptyBuffer)
		return NULL;	
	return buffer;
}

void Buffer::cleanBuffer() {
	notEmptyBuffer = false;
	for (int j = 0; j < i; j++)
	{
		delete[] buffer[j];		
	}
	i = 0;
	free(buffer);
	buffer = (unsigned char**)malloc(sizeof(unsigned char*));
}

Buffer::Buffer() {
	mutexOfBuffer.lock();
	buffer = (unsigned char**)malloc(sizeof(char*));
	mutexOfBuffer.unlock();
}

int Buffer::getNumOfMessage() {
	return i;
}
	
