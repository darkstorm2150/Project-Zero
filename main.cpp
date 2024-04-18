#include <SDL2/SDL.h>
#include <iostream>

bool init();
void kill();
bool load();
bool loop();

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* image1 = NULL;
SDL_Surface* image2 = NULL;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{
		if (!init()) return 1;

		if (!load()) return 1;

		while (loop())
		{
			SDL_Delay(10);
		}

		kill();
		return 0;
}


bool loop()
{
	static bool renderImage2;
	SDL_Event e;

	SDL_BlitSurface(image1, NULL, screenSurface, NULL);
	
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = SCREEN_WIDTH;
	dest.h = SCREEN_HEIGHT;
	SDL_BlitScaled(image1, NULL, screenSurface, &dest);


	if (renderImage2)
	{
		SDL_BlitScaled(image2, NULL, screenSurface, &dest);
	}

	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			renderImage2 = true;
			break;
		case SDL_KEYUP:
			renderImage2 = false;
			break;
		case SDL_MOUSEMOTION:
			break;
		}
	}

	SDL_UpdateWindowSurface(window);

	return true;
}


bool load()
{
	SDL_Surface* temp1, * temp2;

	temp1 = SDL_LoadBMP("zendaya1.bmp");
	temp2 = SDL_LoadBMP("zendaya2.bmp");

	if (!temp1 || !temp2)
	{
		printf("Failed to load image! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	image1 = SDL_ConvertSurface(temp1, screenSurface->format, 0);
	image2 = SDL_ConvertSurface(temp2, screenSurface->format, 0);

	SDL_FreeSurface(temp1);
	SDL_FreeSurface(temp2);

	if (!image1 || !image2)
	{
		printf("Failed converting surface! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

bool init()
{
	if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	
		window = SDL_CreateWindow("SDL2 Initialized!",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}

		screenSurface = SDL_GetWindowSurface(window);
		if (screenSurface == NULL)
		{
			printf("Surface could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		return true;
}

void kill()
{
	printf("Quitting SDL2.\n");
	SDL_FreeSurface(image1);
	SDL_FreeSurface(image2);

	SDL_DestroyWindow(window);
	SDL_Quit();
}