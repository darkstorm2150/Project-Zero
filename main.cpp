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
SDL_Surface* image5 = NULL;
SDL_Surface* image6 = NULL;

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
	static bool renderImage5 = false;
	static bool renderImage6 = false;

	SDL_Event e;

	// SDL_BlitSurface(image1, NULL, screenSurface, NULL);
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = SCREEN_WIDTH;
	src.h = SCREEN_HEIGHT;


	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = SCREEN_WIDTH;
	dest.h = SCREEN_HEIGHT;
    // SDL_BlitScaled(image5, &src, screenSurface, &dest);	

	while (true)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				return false;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					return false;
					break;
				case SDLK_q:
					renderImage1 = true;
					break;
				case SDLK_w:
					renderImage2 = true;
					break;
				case SDLK_e:
					renderImage3 = true;
					break;
				case SDLK_r:
					renderImage4 = true;
					break;
				case SDLK_t:
					renderImage5 = true;
					break;
				case SDLK_y:
					renderImage6 = true;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (e.key.keysym.sym) {
				case SDLK_q:
					renderImage1 = false;
					break;
				case SDLK_w:
					renderImage2 = false;
					break;
				case SDLK_e:
					renderImage3 = false;
					break;
				case SDLK_r:
					renderImage4 = false;
					break;
				case SDLK_t:
					renderImage5 = false;
					break;
				case SDLK_y:
					renderImage6 = false;
					break;
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				switch (e.button.button) {
				case SDL_BUTTON_LEFT:
					renderImage1 = true;
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (e.button.button) {
				case SDL_BUTTON_LEFT:
					renderImage3 = true;
					break;
				}
				break;
			}

		break;
		}

		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));

		if (renderImage1 && image1 && screenSurface)
		{
			SDL_BlitScaled(image1, &src, screenSurface, &dest);
		}

		if (renderImage2 && image2 && screenSurface)
		{
			SDL_BlitScaled(image2, &src, screenSurface, &dest);
		}

		if (renderImage3 && image3 && screenSurface)
		{
			SDL_BlitScaled(image3, &src, screenSurface, &dest);
		}

		if (renderImage4 && image4 && screenSurface)
		{
			SDL_BlitScaled(image4, &src, screenSurface, &dest);
		}

		if (renderImage5 && image5 && screenSurface)
		{
			SDL_BlitScaled(image5, &src, screenSurface, &dest);
		}

		if (renderImage6 && image6 && screenSurface)
		{
			SDL_BlitScaled(image6, &src, screenSurface, &dest);
		}

		SDL_UpdateWindowSurface(window);
	}

	return true;
}


bool load()
{
	SDL_Surface* temp1, * temp2, * temp3, * temp4 , * temp5, * temp6= NULL;

	temp1 = SDL_LoadBMP("zendaya1.bmp");
	temp2 = SDL_LoadBMP("zendaya2.bmp");
	temp3 = SDL_LoadBMP("castle.bmp");
	temp4 = SDL_LoadBMP("livingroom.bmp");
	temp5 = SDL_LoadBMP("menu.bmp");
	temp6 = SDL_LoadBMP("outdoors.bmp");


	if (!temp1 || !temp2 || !temp3 || !temp4 || !temp5 || !temp6)
	{
		printf("Failed to load image! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// add error handling for convertsurface's

	image1 = SDL_ConvertSurface(temp1, screenSurface->format, 0);
	if (!image1)
	{
		std::cout << "Failed to load image1:" << SDL_GetError() << "(SDL ERROR)" << std::endl;
			return false;
	}

	image2 = SDL_ConvertSurface(temp2, screenSurface->format, 0);
	if (!image2)
	{
		std::cout << "Failed to load image2:" << SDL_GetError() << "(SDL ERROR)" << std::endl;
		return false;
	}

	image3 = SDL_ConvertSurface(temp3, screenSurface->format, 0);
	if (!image3)
	{
		std::cout << "Failed to load image3:" << SDL_GetError() << "(SDL ERROR)" << std::endl;
		return false;
	}

	image4 = SDL_ConvertSurface(temp4, screenSurface->format, 0);
	if (!image4)
	{
		std::cout << "Failed to load image4:" << SDL_GetError() << "(SDL ERROR)" << std::endl;
		return false;
	}

	image5 = SDL_ConvertSurface(temp5, screenSurface->format, 0);
	if (!image5)
	{
		std::cout << "Failed to load image5:" << SDL_GetError() << "(SDL ERROR)" << std::endl;
		return false;
	}

	image6 = SDL_ConvertSurface(temp6, screenSurface->format, 0);
	if (!image6)
	{
		std::cout << "Failed to load image6:" << SDL_GetError() << "(SDL ERROR)" << std::endl;
		return false;
	}

	SDL_FreeSurface(temp1);
	SDL_FreeSurface(temp2);
	SDL_FreeSurface(temp3);
	SDL_FreeSurface(temp4);
	SDL_FreeSurface(temp5);
	SDL_FreeSurface(temp6);

	if (!image1 || !image2 || !image3 || !image4 || !image5 || !image6)
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
	SDL_FreeSurface(image4);
	SDL_FreeSurface(image5);
	SDL_FreeSurface(image6);

	SDL_DestroyWindow(window);
	SDL_Quit();
}