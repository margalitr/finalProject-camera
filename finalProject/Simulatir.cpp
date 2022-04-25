#include "Simulatir.h"
#include <thread>
#include <mutex>
Simulatir::Simulatir() {
	start(2);
}
void Simulatir::start(int numOfCanera) {
	std::thread * threadsOfCameras[2];// = (std::thread*)malloc(numOfCanera * sizeof(std::thread));
	for (int i = 0; i < numOfCanera; i++) {
		std::thread camera(runCamera, camers[i]);
		//--------------------------//
		threadsOfCameras[i] = camera;
	}
	
}
void runCamera(Camera camera) {
	camera.run();
}