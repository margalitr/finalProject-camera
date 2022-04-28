#pragma once
#ifndef RANDOM
#define RANDOM
#include <mutex>
float getProb(int min,int max);
static std::mutex mutexOfBuffer;

#endif // !RANDOM
