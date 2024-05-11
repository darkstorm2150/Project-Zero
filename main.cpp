#include <iostream>
#include <SDL.h>
#include <SDL2\SDL_image.h>
#include <cmath>
#include <sstream>

const std::string ProjectZeroVersion = "0.01";

bool initRenderer();
bool loop();
void kill();

// Pointers to our window, renderer, and texture
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;

bool initRenderer() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw std::runtime_error("initRenderer(): Unable to initialize SDL2: " + std::string(SDL_GetError()));
	}

	window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (!window) {
		throw std::runtime_error("initRenderer(): Unable to create primary window: " + std::string(SDL_GetError()));
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		throw std::runtime_error("initRenderer(): Unable to create renderer: " + std::string(SDL_GetError()));
	}

	SDL_Surface* buffer = SDL_LoadBMP("menu.bmp");
	if (!buffer) {
		throw std::runtime_error(std::string("initRenderer(): Unable to load 'menu.bmp': ") + SDL_GetError());
	}

	texture = SDL_CreateTextureFromSurface(renderer, buffer);
	SDL_FreeSurface(buffer);
	buffer = NULL;
	if (!texture) {
		throw std::runtime_error(std::string("initRenderer(); Unable to create texture: ") + std::string(SDL_GetError()));
	}

	return true;
}

bool loop() {

	static const unsigned char* keys = SDL_GetKeyboardState(NULL);

	SDL_Event e;
	SDL_Rect dest;

	static int mx = -1, my = -1;
	static double rot = 0;

	// Clear the window to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	// Event loop
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
		case SDL_QUIT:
			return false;
		case SDL_MOUSEMOTION:
			mx = e.motion.x;
			my = e.motion.y;
			break;
		}
	}

	if (mx != -1) {
		// Distance across window
		float wpercent = mx / 640.0f;
		float hpercent = my / 480.0f;

		// Color
		unsigned char r = round(wpercent * 255);
		unsigned char g = round(hpercent * 255);

		// Color mod (b will always be zero)
		SDL_SetTextureColorMod(texture, r, g, 0);

		mx -= 320;
		my -= 240;
		rot = atan((float)my / (float)mx) * (180.0f / 3.14f);
		if (mx < 0)
			rot -= 180;
	}
	mx = my = -1;

	// Render texture
	dest.x = 240;
	dest.y = 180;
	dest.w = 160;
	dest.h = 120;
	SDL_RenderCopyEx(renderer, texture, NULL, &dest, rot, NULL, keys[SDL_SCANCODE_F] ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);

	// Update window
	SDL_RenderPresent(renderer);

	return true;
}

void kill() {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	texture = NULL;
	window = NULL;
	renderer = NULL;
	SDL_Quit();
}

int main(int argc, char* args[]) {

	std::cout << "Starting Project Zero-SDL2 version " << ProjectZeroVersion << " by Victor Espinoza." << std::endl;

	if (!initRenderer()) return 1;

	while (loop()) {
		// wait before processing the next frame
		SDL_Delay(10);
	}

	kill();
	return 0;
}