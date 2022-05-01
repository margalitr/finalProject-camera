#include "Simulatir.h"
#include <iostream>
#include <thread>
//#include <vector>
#include <stdio.h>

#define Time 3
using namespace std;
using namespace std::literals::chrono_literals;
std::thread * threadsOfRunCameras;
std::thread * threadsOfSendCameras;
std::thread * threadsOfStopCameras;

Simulatir::Simulatir(int numOfCamera) {
	//std::cout << "lll"<<'\n';
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
	//std::thread * cameraRun[numOfCamera];
	//std::thread* threadsOfRunCameras;
	threadsOfRunCameras = new thread[numOfCamera ];
	threadsOfSendCameras = new thread[numOfCamera];
	threadsOfStopCameras = new thread[numOfCamera];
	//threadsOfSendCameras = (std::thread*)malloc(numOfCamera * sizeof(std::thread));
	//threadsOfStopCameras = (std::thread*)malloc(numOfCamera * sizeof(std::thread));
	//std::vector<thread> threadsOfSendCameras(numOfCamera);
	//std::vector<thread> threadsOfStopCameras(numOfCamera);
	int i;
	for ( i = 0; i < numOfCamera; i++) {
		threadsOfRunCameras[i]=std::thread(&Camera::run , &cameras[i]);
		//threadsOfSendCameras[i] = std::thread(&sendCamereToServer, &camers[i]);

		threadsOfSendCameras[i] = thread(&Simulatir::sendCamereToServer, this, &cameras[i],Time);
		std::cout << "camera run i= " << i<< '\n';
		////cameraRun.join();
		////threadsOfCameras[i] = camera;
	}
	char x=getchar();
	for ( i = 0; i < numOfCamera; i++) {
		////std::thread cameraStop(stopCamera, camers[i]);
		////camers[i].stop();
		//*(threadsOfStopCameras + (sizeof(std::thread) * i)) = std::thread(&Camera::stop, &camers[i]);

		threadsOfStopCameras[i] = std::thread(&Camera::stop, &cameras[i]);
		std::cout << "camera stop i= " << i<< '\n';
	}
	for (int i = 0; i < numOfCamera; i++)
	{
		threadsOfRunCameras[i].join();
		threadsOfStopCameras[i].join();
		threadsOfSendCameras[i].join();
		//(*(threadsOfStopCameras + (sizeof(std::thread) * i))).join();
	}
	
}
void runCamera(Camera camera) {
	camera.run();
}
void stopCamera(Camera camera) {
	camera.stop();
}
void Simulatir::sendCamereToServer(Camera * camera ,int time) {
	while (camera->getIsActive()) {
	camera->sendToServer();
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
	/*for (int i = 0; i < 6; i++) {
		std::this_thread::sleep_for(1s);
	}*/
	}
}