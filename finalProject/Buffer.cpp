#include <stdio.h>
#include <stdlib.h>
#include "Buffer.h"

Buffer::~Buffer() {
	cleanBuffer();
	i = 0;
}
void Buffer::addToBuffer(unsigned char* newBuffer) {
	buffer = (unsigned char**)realloc(buffer, ++i * sizeof(char*));
	if (!buffer) {
		return;
	}
	buffer[i - 1] = newBuffer;
}
unsigned char** Buffer::getBuffer() {
	return buffer;
}
void Buffer::cleanBuffer() {
	/*for (int j = 0; j < i; j++)
	{
		free(buffer[j]);
	}*/
	free(buffer);
	buffer = 0;
	i = 0;
}