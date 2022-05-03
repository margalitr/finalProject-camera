//#include "Buffer.h";
#include "Simulatir.h"
#include <iostream>
#include "Global.h"
#include "Simulatir.h"
#include "readConfig.h"





int main() {
	connectToServer();
	Simulatir s(getNumCamera());
	std::cout << "i did it!!";
}