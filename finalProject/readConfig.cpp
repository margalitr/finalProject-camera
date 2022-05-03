#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "readConfig.h"
int numOfCameras;
int timeToCamera;
bool reading = false;
void readConfig() {
	fstream newfile;

	newfile.open("../config.txt", ios::in);
	if (newfile.is_open()) {
		string tp;
		getline(newfile, tp);
			cout << tp << "\n";
		int startindex = tp.find('=');
		numOfCameras = stoi(tp.substr(startindex+1,tp.length()- startindex));
		cout << numOfCameras << "\n";
		getline(newfile, tp);
			cout << tp << "\n";
		startindex = tp.find('=');
		timeToCamera = stoi(tp.substr(startindex + 1, tp.length() - startindex));

		cout << timeToCamera << "\n";


		newfile.close(); //close the file object.
		reading = true;
	}


	else {
		cout << "where is the file?\n I didnt find it.";
	}
}
int getNumCamera() {
	if (!reading) {
		readConfig();
	}
	return numOfCameras;
}
int getTime() {
	if (!reading) {
		readConfig();
	}
	return timeToCamera;
}