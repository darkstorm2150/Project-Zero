#include <SDL2/SDL.h>
#include <iostream>

class Game
{
public:
	Game();
	~Game();
	bool initializeSDL();
	bool loadImages();
	bool loop();
	void shutdownSDL();

	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

private:
	SDL_Window* window = NULL;
	SDL_Surface* background = NULL;
	SDL_Surface* message = NULL;
	SDL_Surface* screen = NULL;
	SDL_Surface* castle = NULL;
	SDL_Surface* livingroom = NULL;
	SDL_Surface* menu = NULL;
	SDL_Surface* outdoors = NULL;
};

Game::Game() : 
	window(NULL), 
	background(NULL),
	message(NULL), 
	screen(NULL),
	castle(NULL), 
	livingroom(NULL),
	menu(NULL), 
	outdoors(NULL) {}

Game::~Game()
{
	shutdownSDL();
}



int main(int argc, char* args[])
{
		Game game;
		if (!game.initializeSDL()) return 1;

		if (!game.loadImages()) return 1;

		while (game.loop())
		{
			SDL_Delay(10);
		}

		game.shutdownSDL();
		return 0;
}


bool Game::loop()
{
	static bool renderImage2 = false;
	static bool imageSelection = 1;

	SDL_Event e;

	SDL_BlitSurface(message, NULL, background, NULL);
	
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = SCREEN_WIDTH;
	dest.h = SCREEN_HEIGHT;
	SDL_BlitScaled(message, NULL, background, &dest);


	if (renderImage2)
	{
		SDL_BlitScaled(screen, NULL, background, &dest);
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


bool Game::loadImages()
{
	SDL_Surface* temp1, * temp2, * temp3, * temp4, * temp5, * temp6;

	message = screen = castle = livingroom = menu = outdoors = NULL;

	temp1 = SDL_LoadBMP("zendaya1.bmp");
	if (!temp1)
	{
		std::cout << "Failed to load image 'zendaya1.bmp':" << SDL_GetError() << " (SDL error) " << std::endl;
		return false;
	}

	temp2 = SDL_LoadBMP("zendaya2.bmp");

	if (!temp2)
	{
		std::cout << "Failed to load image 'zendaya2.bmp':" << SDL_GetError() << " (SDL error) " << std::endl;
		return false;
	}

	temp3 = SDL_LoadBMP("castle.bmp");

	if (!temp3)
	{
		std::cout << "Failed to load image 'castle.bmp':" << SDL_GetError() << " (SDL error) " << std::endl;
		return false;
	}

	temp4 = SDL_LoadBMP("livingroom.bmp");

	if (!temp4)
	{
		std::cout << "Failed to load image 'livingroom.bmp':" << SDL_GetError() << " (SDL error) " << std::endl;
		return false;
	}

	temp5 = SDL_LoadBMP("menu.bmp");

	if (!temp5)
	{
		std::cout << "Failed to load image 'menu.bmp':" << SDL_GetError() << " (SDL error) " << std::endl;
		return false;
	}

	temp6 = SDL_LoadBMP("outdoors.bmp");

	if (!temp6)
	{
		std::cout << "Failed to load image 'outdoors.bmp':" << SDL_GetError() << " (SDL error) " << std::endl;
		return false;
	}

	message = SDL_ConvertSurface(temp1, background->format, 0);
	screen = SDL_ConvertSurface(temp2, background->format, 0);
	castle = SDL_ConvertSurface(temp3, background->format, 0);
	livingroom = SDL_ConvertSurface(temp4, background->format, 0);
	menu = SDL_ConvertSurface(temp5, background->format, 0);
	outdoors = SDL_ConvertSurface(temp6, background->format, 0);

	SDL_FreeSurface(temp1);
	SDL_FreeSurface(temp2);
	SDL_FreeSurface(temp3);
	SDL_FreeSurface(temp4);
	SDL_FreeSurface(temp5);
	SDL_FreeSurface(temp6);

	if (!message)
	{
		std::cout << "failed to convert surface for image 1:" << SDL_GetError() << " (SDL error) " << std::endl;
		return false;
	}

	if (!screen)
	{
		std::cout << "failed to convert surface for image 2:" << SDL_GetError() << " (SDL error) " << std::endl;
		return false;
	}

	if (!castle)
	{
		std::cout << "failed to convert surface for image 3:" << SDL_GetError() << " (SDL error) " << std::endl;
		return false;
	}

	if (!livingroom)
	{
		std::cout << "failed to convert surface for image 4:" << SDL_GetError() << " (SDL error) " << std::endl;
		return false;
	}

	if (!menu)
	{
		std::cout << "failed to convert surface for image 5:" << SDL_GetError() << " (SDL error) " << std::endl;
		return false;
	}

	if (!outdoors)
	{
		std::cout << "failed to convert surface for image 6:" << SDL_GetError() << " (SDL error) " << std::endl;
		return false;
	}

	return true;
}

bool Game::initializeSDL()
{
	if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialize:" << SDL_GetError() << " (SDL error) " << std::endl;
	}
	
	window = SDL_CreateWindow("SDL2 Initialized!",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if (window == NULL)
			{
			std::cout << "Window could not be created:" << SDL_GetError() << " (SDL error) " << std::endl;
			}

		background = SDL_GetWindowSurface(window);
		if (background == NULL)
		{
			std::cout << "Surface could not be created:" << SDL_GetError() << " (SDL error) " << std::endl;
		}
		return true;
}

void Game::shutdownSDL()
{
	std::cout << "Shutting down SDL2" << std::endl;

	SDL_DestroyWindow(window);
	SDL_Quit();
}