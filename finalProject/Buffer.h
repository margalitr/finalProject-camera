#pragma once
#ifndef Buffer1
#define Buffer1
class Buffer
{
private:
	unsigned char** buffer;
	int i = 0;
public:
	~Buffer();
	void addToBuffer(unsigned char* newBuffer);
	unsigned char** getBuffer();
	void cleanBuffer();
};

#endif // !Buffer1


