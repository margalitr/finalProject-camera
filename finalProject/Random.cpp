#include "Random.h"
#include <iostream>
#include <random>

int getProb(int min, int max) {
	std::random_device rd;
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
	std::mt19937 mt{ ss };
	std::uniform_int_distribution<int>  _dist(min, max);

	return _dist(mt);
}