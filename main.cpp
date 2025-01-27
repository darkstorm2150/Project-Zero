#include "screen.h"

int main(int argc, char** args)
{
	std::cout << "Starting Project Zero-SDL2 version 0.02 by Victor Espinoza." << std::endl;

	ProjectZero::Screen screen(1280, 720);

	if (!screen.Initialize())
	{
		std::cerr << "Failed to initialize screen. Exiting..." << SDL_GetError() << std::endl;
		return 1;
	}

	screen.RunEventLoop();

	// Clean up
	screen.Cleanup();

	return 0;
}