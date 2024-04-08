#define SDL_MAIN_HANDLED

#include <iostream>
#include "application.hpp"
#include <SDL2\SDL.h> // Using SDL and standard IO
#include <stdio.h>



int main()
{
	// The window to render to
	SDL_Window* window = nullptr;

	// The surface contained by the window
	SDL_Surface* screenSurface = nullptr;

	// Test image

	SDL_Surface* image = SDL_LoadBMP("zendaya.bmp");
	if (!image)
	{
		std::cout << "Failed to laod image\n";
		std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
		return -1;
	}

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf( "SDL could not initialize! SDL_ERROR: %s\n", SDL_GetError() );
	}
	else
	{
		// Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			// Get window surface
			screenSurface = SDL_GetWindowSurface( window );

			// Fill the surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			// Update the surface
			SDL_UpdateWindowSurface( window );

			// test section for BMP
			SDL_BlitSurface(image, NULL, screenSurface, NULL);
			SDL_UpdateWindowSurface(window);


			// Hack to get window to stay up
			SDL_Event e; bool quit = false; while (quit == false) {
				while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
		}
	}

	// Destroy window
	SDL_DestroyWindow( window );

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}