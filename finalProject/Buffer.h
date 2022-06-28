#pragma once
#ifndef Buffer1
#define Buffer1
#include <mutex>
class Buffer
{
private:
	unsigned char** buffer;
	int i =0;
	bool notEmptyBuffer = false;

public:
	std::mutex mutexOfBuffer;
	Buffer();
	~Buffer();
	void addToBuffer(unsigned char* newBuffer);
	unsigned char** getBuffer();
	void cleanBuffer();
	int getNumOfMessage();
	
};

#endif // !Buffer1


