#include "screen.h"

int main(int argc, char** args)
{
	std::cout << "Starting Project Zero-SDL2 version 0.02 by Victor Espinoza." << std::endl;

	Screen screen(1280, 720);

	if (!screen.init())
	{
		return 1;
	}

	screen.eventLoop();

	return 0;
}