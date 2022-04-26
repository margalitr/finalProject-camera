#pragma once
#ifndef CAMARA
#define CAMARA
#include "Message.h"
#include "Buffer.h"
class Camera
{

private:
	static char numOfCameras;
	char id;
	BaseMessage** messages;
	int indexMessages=0;
	Buffer buffer;
	bool isActive;
public:
	Camera();
	~Camera();
	void stop();
	void run();
	void sendToBuffer();
	void generate();
	void sendToServer();
	bool getIsActive();
};
#endif // !Camera



