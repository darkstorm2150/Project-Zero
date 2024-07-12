#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

class Screen
{
public:
	Screen(int width, int height);
	~Screen();

	bool init();
	void eventLoop();
	void cleanup();

	TTF_Font* init_font(const char* font_file, int font_size);
	bool create_buttons(TTF_Font* font, SDL_Surface** button_surfaces, SDL_Rect* button_rects, const char** button_labels);
	void render_menu(SDL_Surface* surface, SDL_Surface* button_surfaces[], SDL_Rect button_rects[], int currentSelection);
	void handle_events(SDL_Event* e, bool* quit, int* currentSelection, SDL_Window* window, SDL_Surface* surface, TTF_Font* font, const char* button_labels[]);
	void render_button(SDL_Surface* surface, SDL_Surface* button_surface, SDL_Rect* rect);
	SDL_Surface* displayLoginScreen(SDL_Window* window, SDL_Surface* surface, TTF_Font* font);

	SDL_Surface* create_button_surface(TTF_Font* font, SDL_Color color, const char* text, SDL_Rect* rect);

private:
	SDL_Window* window_;
	SDL_Surface* surface_;
	TTF_Font* font_;
	SDL_Surface* button_surface_[4];
	SDL_Rect button_rect_[4];
	const char* button_labels_[4];
	int currentSelection_;
	bool quit_;
};

#endif // SCREEN_H
