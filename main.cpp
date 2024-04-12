#include <SDL2/SDL.h>
#include <iostream>


int main(int argc, char* args[])
{
	SDL_SetError("Simulated initialization error");

	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
	}

	return 0;
}