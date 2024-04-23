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
SDL_Surface* image3 = NULL;
SDL_Surface* image4 = NULL;

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
	static bool renderImage1 = false;
	static bool renderImage2 = false;
	static bool renderImage3 = false;
	static bool renderImage4 = false;



	SDL_Event e;

	// SDL_BlitSurface(image1, NULL, screenSurface, NULL);

	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = SCREEN_WIDTH;
	dest.h = SCREEN_HEIGHT;
	SDL_BlitScaled(image1, NULL, screenSurface, &dest);


	if (renderImage1)
	{
		SDL_BlitScaled(image1, NULL, screenSurface, &dest);
	}

	if (renderImage2)
	{
		SDL_BlitScaled(image2, NULL, screenSurface, &dest);
	}

	if (renderImage3)
	{
		SDL_BlitScaled(image3, NULL, screenSurface, &dest);
	}

	if (renderImage4)
	{
		SDL_BlitScaled(image4, NULL, screenSurface, &dest);
	}

	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_q:
				renderImage1 = true;
				break;
			case SDLK_a:
				renderImage1 = false;
				break;
			case SDLK_w:
				renderImage2 = true;
				break;
			case SDLK_s:
				renderImage2 = false;
				break;
			case SDLK_e:
				renderImage3 = true;
				break;
			case SDLK_d:
				renderImage3 = false;
				break;
			case SDLK_r:
				renderImage4 = true;
				break;
			case SDLK_f:
				renderImage4 = false;
				break;
			}
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
	SDL_Surface* temp1, * temp2, * temp3, * temp4 = NULL;

	temp1 = SDL_LoadBMP("zendaya1.bmp");
	temp2 = SDL_LoadBMP("zendaya2.bmp");
	temp3 = SDL_LoadBMP("castle.bmp");
	temp4 = SDL_LoadBMP("livingroom.bmp");

	if (!temp1 || !temp2 || !temp3 || !temp4)
	{
		printf("Failed to load image! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	image1 = SDL_ConvertSurface(temp1, screenSurface->format, 0);
	image2 = SDL_ConvertSurface(temp2, screenSurface->format, 0);
	image3 = SDL_ConvertSurface(temp3, screenSurface->format, 0);
	image4 = SDL_ConvertSurface(temp4, screenSurface->format, 0);

	SDL_FreeSurface(temp1);
	SDL_FreeSurface(temp2);
	SDL_FreeSurface(temp3);
	SDL_FreeSurface(temp4);

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
	SDL_FreeSurface(image3);

	SDL_DestroyWindow(window);
	SDL_Quit();
}