#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <cmath>
#include <sstream>

// Font 8_bit_1_6 by Zaydek MG

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_SPACING 20

const std::string ProjectZeroVersion = "0.01";

// Function to create a button
SDL_Surface* create_button(TTF_Font* font, SDL_Color color, const char* text, SDL_Rect* rect)
{
	SDL_Surface* button_surface = TTF_RenderText_Solid(font, text, color);
	rect->w = button_surface->w;
	rect->h = button_surface->h;
	return button_surface;
}

// Function to render a button
void renderButton(SDL_Surface* surface, SDL_Surface* buttonSurface, SDL_Rect* rect)
{
	SDL_BlitSurface(buttonSurface, NULL, surface, rect);
}

// Function to render a button
void render_button(SDL_Surface* surface, SDL_Surface* button_surface, SDL_Rect* rect)
{
	SDL_BlitSurface(button_surface, NULL, surface, rect);
}

// Function to initialize SDL
bool init_sdl(SDL_Window** window, SDL_Surface** surface)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL Initialize failed: %s\n", SDL_GetError());
		return 1;
	}

	*window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

	if (!*window)
	{
		printf("Window creation failed: %s\n", SDL_GetError());
		return 1;
	}

	*surface = SDL_GetWindowSurface(*window);
	return true;
}

// Function to load font and create buttons
bool load_font_and_create_buttons(TTF_Font** font, SDL_Surface** button_surfaces, SDL_Rect* button_rects, const char** button_labels)
{
	if (TTF_Init() < 0)
	{
		printf("TTF Initialization failed: %s\n", TTF_GetError());
		return 1;
	}

	*font = TTF_OpenFont("8bit16.ttf", 48);
	if (!*font)
	{
		printf("TTF Initialization failed: %s\n", TTF_GetError());
		return 1;
	}

	SDL_Color button_color = { 255, 255 , 255 };

	for (int i = 0; i < 4; i++)
	{
		button_rects[i].x = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
		button_rects[i].y = 200 + i * (BUTTON_HEIGHT + BUTTON_SPACING);
		button_surfaces[i] = create_button(*font, button_color, button_labels[i], &button_rects[i]);
	}

	return true;
}

int main(int argc, char** args)
{
	std::cout << "Starting Project Zero-SDL2 version " << ProjectZeroVersion << " by Victor Espinoza." << std::endl;

	SDL_Window* window = NULL;
	SDL_Surface* surface = NULL;
	TTF_Font* font = NULL;

	// Create button surfaces and rects
	SDL_Surface* button_surfaces[4];
	SDL_Rect button_rects[4];
	const char* button_labels[] = { "Login", "Register", "Exist", "Help" };

	if (!init_sdl(&window, &surface))
	{
		return 1;
	}

	if (!load_font_and_create_buttons(&font, button_surfaces, button_rects, button_labels))
	{
		return 1;
	}

	static const unsigned char* keys = SDL_GetKeyboardState(NULL);

	SDL_Event e;
	SDL_Rect dest;

	// Event loop
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_QUIT:
				quit = true;
				return false;
			case SDL_KEYDOWN:
				break;
			}
		}

		// Render everything
		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
		for (int i = 0; i < 4; i++)
		{
			render_button(surface, button_surfaces[i], &button_rects[i]);
		}

		SDL_UpdateWindowSurface(window);
	}
	
	// Clean up
	for (int i = 0; i < 4; i++)
	{
		SDL_FreeSurface(button_surfaces[i]);
	}

	TTF_CloseFont(font);
	font = NULL;

	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

	return 0;
}