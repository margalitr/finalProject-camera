#pragma once
#ifndef READ_CONFIG_H
#define READ_CONFIG_H

class ReadConfig {
protected:
	int numOfCameras=0;
	int timeToCamera=0;
	int port=0;
private:
	static ReadConfig* instance;
	ReadConfig();
public:
	static ReadConfig*  getReadInstance();
	int getTime();
	int getNumCamera();
	int getPort();
};

#endif // !READ_CONFIG_H
