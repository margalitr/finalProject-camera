
#include <iostream>
#include "Global.h"
#include "Simulatir.h"
#include "readConfig.h"

int main() {
	connectToServer();
	Simulatir s(ReadConfig::getReadInstance()->getNumCamera());
	std::cout << "i did it!!";
}