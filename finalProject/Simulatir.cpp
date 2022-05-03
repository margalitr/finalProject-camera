#include "Simulatir.h"
#include <iostream>
#include <thread>
#include <stdio.h>

#define Time 3
using namespace std;
using namespace std::literals::chrono_literals;
std::thread * threadsOfRunCameras;
std::thread * threadsOfSendCameras;
std::thread * threadsOfStopCameras;

Simulatir::Simulatir(int numOfCamera) {
	cameras=new Camera[numOfCamera];
	startSimulatir(numOfCamera);
}
Simulatir::~Simulatir() {
	delete []threadsOfRunCameras;	
	delete[]threadsOfSendCameras;
	delete[]threadsOfStopCameras;
	delete[] cameras;
}
void Simulatir::startSimulatir(int numOfCamera) {
	threadsOfRunCameras = new thread[numOfCamera ];
	threadsOfSendCameras = new thread[numOfCamera];
	threadsOfStopCameras = new thread[numOfCamera];
	int i;
	for ( i = 0; i < numOfCamera; i++) {
		threadsOfRunCameras[i]=std::thread(&Camera::run , &cameras[i]);
		threadsOfSendCameras[i] = thread(&Simulatir::sendCamereToServer, this, &cameras[i],Time);
		std::cout << "camera run i= " << i<< '\n';
	}
	char x=getchar();
	for ( i = 0; i < numOfCamera; i++) {
		threadsOfStopCameras[i] = std::thread(&Camera::stop, &cameras[i]);
		std::cout << "camera stop i= " << i<< '\n';
	}
	for (int i = 0; i < numOfCamera; i++)
	{
		threadsOfRunCameras[i].join();
		threadsOfStopCameras[i].join();
		threadsOfSendCameras[i].join();
	}
	
}
void runCamera(Camera camera) {
	camera.run();
}
void stopCamera(Camera camera) {
	camera.stop();
}
void Simulatir::sendCamereToServer(Camera * camera ,int time) {
	camera->connectToServer();
	while (camera->getIsActive()) {
	camera->sendToServer();
	std::cout << "send !!!!!!!!!!!!!";
	for (int i = 0; i < time; i++) {
		std::this_thread::sleep_for(1s);
	}
	}
}