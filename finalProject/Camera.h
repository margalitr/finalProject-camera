#pragma once
#ifndef CAMARA
#define CAMARA
#include "Message.h"
#include "Buffer.h"
class Camera
{
private:
	char id;
	BaseMessage** messages;
	int indexMessages;
	Buffer buffer;
	bool isActive;
public:
	Camera();
	void stop();
	void run();
	void sendToBuffer();
	void generate();
};
#endif // !Camera



