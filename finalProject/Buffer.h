#pragma once
#ifndef Buffer1
#define Buffer1
#include <mutex>
class Buffer
{
private:
	unsigned char** buffer;
	int i =0;
public:
	Buffer();
	~Buffer();
	void addToBuffer(unsigned char* newBuffer);
	unsigned char** getBuffer();
	void cleanBuffer();
	int getNumOfMessage();
	void print();
};

#endif // !Buffer1


