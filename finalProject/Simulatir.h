#pragma once
#include "Camera.h"
#ifndef SIMULATIR
#define SIMULATIR

class Simulatir
{
private:
	Camera camers[2];
public:
	Simulatir();
	void start(int numOffCamera);
};
void stopCamera(Camera camera);
void runCamera(Camera camera);
void sendCamereToServer(Camera camera, int time);
#endif // !SIMULATIR


