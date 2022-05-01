#include "Global.h"
#include <iostream>
#include <random>

float getProb(int min, int max) {
	std::random_device rd;
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
	std::mt19937 mt{ ss };
	std::uniform_real_distribution<float>  _dist(min, max+1);

	return _dist(mt);
}

