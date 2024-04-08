#define SDL_MAIN_HANDLED

#include <iostream>
#include "application.hpp"
#include <SDL2\SDL.h> // Using SDL and standard IO
#include <stdio.h>



int main()
{
	Application app;
	app.update();
	app.draw();

	return 0;
}