#pragma once
#ifndef CAMARA
#define CAMARA
#include "Message.h"
#include "Buffer.h"
#include <mutex>

class Camera {
private:
	static char numOfCameras;
	static std::mutex m;
	char id;
	BaseMessage** messages;
	int indexMessages1;
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



