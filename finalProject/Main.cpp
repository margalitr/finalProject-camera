#include "Buffer.h";
#include <iostream>
int main() {
	Buffer b;
	unsigned char contents[]{ "lll" };
	b.addToBuffer(contents);
	b.addToBuffer(contents);
	unsigned char** buffers = b.getBuffer();
	for (int i = 0; i < 2; i++)
	{
		std::cout << buffers[i] << '\n';
	}
}