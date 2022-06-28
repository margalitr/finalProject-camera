#include <iostream>
#include <fstream>
#include <string>
#include "readConfig.h"
using namespace std;

ReadConfig* ReadConfig::instance = 0;

ReadConfig* ReadConfig::getReadInstance() {
	if (ReadConfig::instance == NULL) {
		ReadConfig::instance = new ReadConfig();
	}
	return instance;
}

ReadConfig::ReadConfig() {
	fstream file;
	file.open("../config.txt", ios::in);
	if (file.is_open()) {
		string tp;
		getline(file, tp);
		int startindex = tp.find('=');
		numOfCameras = stoi(tp.substr(startindex + 1, tp.length() - startindex));
		getline(file, tp);
		startindex = tp.find('=');
		timeToCamera = stoi(tp.substr(startindex + 1, tp.length() - startindex));
		getline(file, tp);
		startindex = tp.find('=');
		port = stoi(tp.substr(startindex + 1, tp.length() - startindex));
		file.close();
	}
	else {
		cout << "where is the file?\n I didnt find it.";
	}
}

int ReadConfig::getNumCamera() {
	return numOfCameras;
}

int ReadConfig::getTime() {
	return timeToCamera;
}

int ReadConfig::getPort() {
	return port;
}