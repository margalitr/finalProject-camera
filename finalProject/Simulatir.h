#pragma once
#include "Camera.h"
#ifndef SIMULATIR
#define SIMULATIR

class Simulatir
{
private:

	Camera* cameras;
public:
	Simulatir(int numOfCamera);
	void startSimulatir(int numOfCamera);
	~Simulatir();
	void sendCamereToServer(Camera * camera, int time);


};
void stopCamera(Camera camera);
void runCamera(Camera camera);

#endif // !SIMULATIR


