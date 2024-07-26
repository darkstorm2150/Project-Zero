#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

namespace ProjectZero
{
	class Screen
	{
	public:
		// Constructor
		Screen(int width, int height);
		
		// Destructor
		~Screen();

		// Initialize the Screen
		bool Initialize();

		// Runs the event loop
		void RunEventLoop();

		// Cleans up resources
		void Cleanup();

		// Initialize a font
		TTF_Font* InitializeFont(const char* fontFile, int fontSize);
		
		// Creates buttons
		bool CreateButtons(TTF_Font* font, SDL_Surface** buttonSurfaces, SDL_Rect* buttonRects, const char** buttonLabels);
		
		// Renders the menu
		void RenderMenu(SDL_Surface* surface, SDL_Surface* buttonSurfaces[], SDL_Rect buttonRects[], int currentSelection);
		
		// Handles events
		void HandleEvents(SDL_Event* e, bool* quit, int* currentSelection, SDL_Window* window, SDL_Surface* surface, TTF_Font* font, const char* buttonLabels[]);
		
		// Renders a button
		void RenderButton(SDL_Surface* surface, SDL_Surface* buttonSurface, SDL_Rect* rect);
		
		// Displays the Login screen
		SDL_Surface* DisplayLoginScreen(SDL_Window* window, SDL_Surface* surface, TTF_Font* font);

		// Crates a button surface
		SDL_Surface* CreateButtonSurface(TTF_Font* font, SDL_Color color, const char* text, SDL_Rect* rect);

	private:
		// Window handle
		SDL_Window* window_;

		// Surface handle
		SDL_Surface* surface_;

		// Font handle
		TTF_Font* font_;

		// Button Surface
		SDL_Surface* buttonSurface_[4];

		// Button rectangles
		SDL_Rect buttonRect_[4];

		// Button Labels
		const char* buttonLabels_[4];

		// Current selection
		int currentSelection_;

		// Quit flag
		bool quit_;

		// Login Surface
		SDL_Surface* login_surface_;
	};
}

#endif // SCREEN_H
