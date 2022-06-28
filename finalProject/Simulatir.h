#pragma once
#include "Camera.h"
#ifndef SIMULATIR
#define SIMULATIR

class Simulatir
{
private:
	Camera* cameras;
	std::thread* threadsOfRunCameras;
	std::thread* threadsOfSendCameras;
	std::thread* threadsOfStopCameras;

public:
	Simulatir(int numOfCamera);
	void startSimulatir(int numOfCamera);
	~Simulatir();
	void sendCamereToServer(Camera * camera, int time);
};

void stopCamera(Camera camera);
void runCamera(Camera camera);
void sending(char*, int);

#endif //!SIMULATIR


