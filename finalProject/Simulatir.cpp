#include "Simulatir.h"
#include <iostream>
#include <thread>
#include <vector>
#define Time 3
using namespace std;
using namespace std::literals::chrono_literals;
Simulatir::Simulatir() {
	std::cout << "lll";
	start(2);
}
void Simulatir::start(int numOfCamera) {
	//std::thread * cameraRun;
	std::vector<thread> threadsOfRunCameras(numOfCamera);
	std::vector<thread> threadsOfSendCameras(numOfCamera);
	std::vector<thread> threadsOfStopCameras(numOfCamera);
	int i;
	for ( i = 0; i < numOfCamera; i++) {
		threadsOfRunCameras[i]=thread(runCamera, camers[i]);
		threadsOfSendCameras[i] = thread(sendCamereToServer, camers[i],Time);
		std::cout << "camera run i= " << i<< '\n';
		//cameraRun.join();
		//threadsOfCameras[i] = camera;
	}
	getchar();
	for ( i = 0; i < numOfCamera; i++) {
		//std::thread cameraStop(stopCamera, camers[i]);
		//camers[i].stop();
		threadsOfStopCameras[i] = thread(stopCamera, camers[i]);
		//threadsOfStopCameras[i] = thread(stopCamera, camers[i]);
		std::cout << "camera stop i= " << i<< '\n';
		threadsOfStopCameras[i].join();
		threadsOfRunCameras[i].join();
		threadsOfSendCameras[i].join();
	}
	
}
void runCamera(Camera camera) {
	camera.run();
}
void stopCamera(Camera camera) {
	camera.stop();
}
void sendCamereToServer(Camera camera,int time) {
	while (camera.getIsActive()) {
	camera.sendToServer();
	for (int i = 0; i < time; i++) {
		std::this_thread::sleep_for(1s);
	}
	}
}