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

#endif // !SIMULATIR


