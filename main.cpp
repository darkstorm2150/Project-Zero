#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 1320;
const int SCREEN_HEIGHT = 743;


int main(int argc, char* args[])
{
	SDL_Window* window = NULL;

	SDL_Surface* screenSurface = NULL;

	SDL_Surface* photo = NULL;

	if ( SDL_InitSubSystem( SDL_INIT_EVERYTHING ) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("SDL2 Initialized!", 
								   SDL_WINDOWPOS_UNDEFINED, 
								   SDL_WINDOWPOS_UNDEFINED, 
								   SCREEN_WIDTH, 
								   SCREEN_HEIGHT, 
								   SDL_WINDOW_SHOWN);
		if ( window == NULL )
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
			
			// Uint32 white = SDL_MapRGB(screenSurface->format, 255, 255, 255 );
			
			// SDL_FillRect(screenSurface, NULL, white);
			
			photo = SDL_LoadBMP("zendaya.bmp");

			if (photo == NULL)
			{
				printf("Failed to load image! SDL_Error: %s\n", SDL_GetError());
			}
			else
			{
				SDL_BlitSurface(photo, NULL, screenSurface, NULL);
				SDL_UpdateWindowSurface(window);
			}

			SDL_FreeSurface(photo);
			photo = NULL;


			photo = SDL_LoadBMP("zendaya2.bmp");

			if (photo == NULL)
			{
				printf("Failed to load image! SDL_Error: %s\n", SDL_GetError());
			}
			else
			{
				SDL_BlitSurface(photo, NULL, screenSurface, NULL);
				SDL_UpdateWindowSurface(window);
			}
			
			SDL_FreeSurface(photo);
			photo = NULL;

			SDL_Event event; 
			bool running = true;
			
			while ( running ) 
			{
				while (SDL_PollEvent(&event)) 
				{ 
					if ( event.type == SDL_QUIT )
					{
						running = false;
						break;
					}
				}
			}
		}
	}

	printf("Quitting SDL2.\n");

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}