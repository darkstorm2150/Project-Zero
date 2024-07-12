#include "screen.h"
#include <cstdio>

Screen::Screen(int width, int height) : window_(nullptr), surface_(nullptr), font_(nullptr), currentSelection_(0), quit_(false)
{
	button_labels_[0] = "Login";
	button_labels_[1] = "Register";
	button_labels_[2] = "Exit";
	button_labels_[3] = "Help";
}

Screen::~Screen()
{
	cleanup();
}

bool Screen::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL Initialize failed: %s\n", SDL_GetError());
		return false;
	}

	window_ = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

	if (!window_)
	{
		printf("Window creation failed: %s\n", SDL_GetError());
		return false;
	}

	surface_ = SDL_GetWindowSurface(window_);
	font_ = init_font("8bit16.ttf", 48);
	if (!font_)
	{
		return false;
	}

	if (!create_buttons(font_, button_surface_, button_rect_, button_labels_))
	{
		return false;
	}

	return true;
}

void Screen::eventLoop()
{
	SDL_Event e;

	while (!quit_)
	{
		render_menu(surface_, button_surface_, button_rect_, currentSelection_);
		SDL_UpdateWindowSurface(window_);

		handle_events(&e, &quit_, &currentSelection_, window_, surface_, font_, button_labels_);
	}
}

void Screen::cleanup()
{
	for (int i = 0; i < 4; i++)
	{
		SDL_FreeSurface(button_surface_[i]);
	}
	TTF_CloseFont(font_);
	font_ = nullptr;
	SDL_DestroyWindow(window_);
	TTF_Quit();
	SDL_Quit();
}

TTF_Font* Screen::init_font(const char* font_file, int font_size)
{
	if (TTF_Init() < 0)
	{
		printf("TTF Initialization Failed: %s\n", TTF_GetError());
		return NULL;
	}
	TTF_Font* font = TTF_OpenFont(font_file, font_size);
	if (!font)
	{
		printf("TTF Font loading failed: %s\n", TTF_GetError());
		return NULL;
	}
	return font;
}

bool Screen::create_buttons(TTF_Font*, SDL_Surface** button_surfaces, SDL_Rect* button_rects, const char** button_labels)
{
	SDL_Color button_colors = { 255, 255, 255 };

	for (int i = 0; i < 4; i++)
	{
		button_rects[i].x = (1280 - 200) / 2;
		button_rects[i].y = 200 + i * (50 + 20);
		button_surfaces[i] = create_button_surface(font_, button_colors, button_labels[i], &button_rects[i]);
	}
	return true;
}

SDL_Surface* Screen::create_button_surface(TTF_Font* font, SDL_Color color, const char* text, SDL_Rect* rect) {
    SDL_Surface* button_surface = TTF_RenderText_Solid(font, text, color);
    rect->w = button_surface->w;
    rect->h = button_surface->h;
    return button_surface;
}

void Screen::render_menu(SDL_Surface* surface, SDL_Surface* button_surfaces[], SDL_Rect button_rects[], int currentSelection) {
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
    TTF_Font* font = init_font("8bit16.ttf", 48);
    const char* button_labels[] = { "login", "register", "Exit", "Help" };
    for (int i = 0; i < 4; i++) {
        if (i == currentSelection) {
            SDL_Color highlightColor = { 255, 255, 0 };
            SDL_Surface* highlightedButton = create_button_surface(font, highlightColor, button_labels[i], &button_rects[i]);
            render_button(surface, highlightedButton, &button_rects[i]);
            SDL_FreeSurface(highlightedButton);
        }
        else {
            render_button(surface, button_surfaces[i], &button_rects[i]);
        }
    }
    TTF_CloseFont(font);
}

void Screen::handle_events(SDL_Event* e, bool* quit, int* currentSelection, SDL_Window* window, SDL_Surface* surface, TTF_Font* font, const char* button_labels[]) {
    while (SDL_PollEvent(e) != 0) {
        if (e->type == SDL_QUIT) {
            *quit = true;
        }
        else if (e->type == SDL_KEYDOWN) {
            switch (e->key.keysym.sym) {
            case SDLK_UP:
                *currentSelection = (*currentSelection - 1 + 4) % 4;
                std::cout << "CurrentSelection Variable:" << *currentSelection << std::endl;
                break;
            case SDLK_DOWN:
                *currentSelection = (*currentSelection + 1) % 4;
                std::cout << "CurrentSelection Variable:" << *currentSelection << std::endl;
                break;
            case SDLK_RETURN:
                switch (*currentSelection) {
                case 0:
                    std::cout << "Login button selected" << std::endl;
                    displayLoginScreen(window, surface, font);
                    break;
                case 1:
                    std::cout << "Register button selected" << std::endl;
                    break;
                case 2:
                    std::cout << "Exit button selected" << std::endl;
                    *quit = true;
                    break;
                case 3:
                    std::cout << "Help button selected" << std::endl;
                    break;
                }
                break;
            }
        }
    }
}

void Screen::render_button(SDL_Surface* surface, SDL_Surface* button_surface, SDL_Rect* rect) {
    SDL_BlitSurface(button_surface, NULL, surface, rect);
}

SDL_Surface* Screen::displayLoginScreen(SDL_Window* window, SDL_Surface* surface, TTF_Font* font) {
    SDL_Surface* login_surface = SDL_CreateRGBSurface(0, 1280, 720, 32, 0, 0, 0, 0);

    SDL_Color text_color = { 255, 255, 255 };
    SDL_Surface* login_text = TTF_RenderText_Solid(font, "Login Screen", text_color);
    SDL_Rect login_rect = { 100, 100, login_text->w, login_text->h };
    SDL_BlitSurface(login_text, NULL, login_surface, &login_rect);
    SDL_FreeSurface(login_text);

    SDL_BlitSurface(login_surface, NULL, surface, NULL);

    SDL_UpdateWindowSurface(window);

    return login_surface;
}