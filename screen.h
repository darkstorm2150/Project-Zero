#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <memory>

namespace ProjectZero
{
	class Screen {
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

		// Create buttons
		void CreateButtons();

		// Render the menu
		void RenderMenu() const;

		// Handle events
		void HandleEvents(SDL_Event* e);

		// Display the login screen
		void DisplayLoginScreen();

	private:
		void RenderLogin() const;

		// Window handle
		std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_;

		// Surface handle
		std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface_;

		// Font handle
		std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font_;

		// Button textures
		std::vector<std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>> buttonTextures_;

		// Button rectangles
		std::vector<SDL_Rect> buttonRects_;

		// Button Labels
		std::vector<std::string> buttonLabels_;

		// Current selection
		int currentSelection_;

		// Screen State
		enum class ScreenState {
			RUNNING,
			QUITTING,
			LOGIN
		};
		ScreenState screenState_;
	};
}

#endif // SCREEN_H
