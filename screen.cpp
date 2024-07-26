#include "screen.h"
#include <cstdio>

ProjectZero::Screen::Screen(int width, int height) : 
    window_(nullptr), 
    surface_(nullptr), 
    font_(nullptr), 
    currentSelection_(0), 
    quit_(false), 
    login_surface_(nullptr), 
    buttonRect_(), 
    buttonSurface_()
{
    buttonLabels_[0] = "Login";
    buttonLabels_[1] = "Register";
    buttonLabels_[2] = "Exit";
    buttonLabels_[3] = "Help";
}

ProjectZero::Screen::~Screen()
{
    Cleanup();
}

bool ProjectZero::Screen::Initialize()
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
	font_ = InitializeFont("8bit16.ttf", 48);
	if (!font_)
	{
		return false;
	}

	if (!CreateButtons(font_, buttonSurface_, buttonRect_, buttonLabels_))
	{
		return false;
	}

	return true;
}

void ProjectZero::Screen::RunEventLoop()
{
	SDL_Event e;

	while (!quit_)
	{
		RenderMenu(surface_, buttonSurface_, buttonRect_, currentSelection_);
		SDL_UpdateWindowSurface(window_);

		HandleEvents(&e, &quit_, &currentSelection_, window_, surface_, font_, buttonLabels_);
	}
}

TTF_Font* ProjectZero::Screen::InitializeFont(const char* font_file, int font_size)
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

bool ProjectZero::Screen::CreateButtons(TTF_Font*, SDL_Surface** button_surfaces, SDL_Rect* button_rects, const char** button_labels)
{
	SDL_Color button_colors = { 255, 255, 255 };

	for (int i = 0; i < 4; i++)
	{
		button_rects[i].x = (1280 - 200) / 2;
		button_rects[i].y = 200 + i * (50 + 20);
		button_surfaces[i] = CreateButtonSurface(font_, button_colors, button_labels[i], &button_rects[i]);
	}
	return true;
}

SDL_Surface* ProjectZero::Screen::CreateButtonSurface(TTF_Font* font, SDL_Color color, const char* text, SDL_Rect* rect) {
    SDL_Surface* button_surface = TTF_RenderText_Solid(font, text, color);
    rect->w = button_surface->w;
    rect->h = button_surface->h;
    return button_surface;
}

void ProjectZero::Screen::RenderMenu(SDL_Surface* surface, SDL_Surface* button_surfaces[], SDL_Rect button_rects[], int currentSelection) {
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
    TTF_Font* font = InitializeFont("8bit16.ttf", 48);
    const char* button_labels[] = { "login", "register", "Exit", "Help" };
    for (int i = 0; i < 4; i++) {
        if (i == currentSelection) {
            SDL_Color highlightColor = { 255, 255, 0 };
            SDL_Surface* highlightedButton = CreateButtonSurface(font, highlightColor, button_labels[i], &button_rects[i]);
            RenderButton(surface, highlightedButton, &button_rects[i]);
            SDL_FreeSurface(highlightedButton);
        }
        else {
            RenderButton(surface, button_surfaces[i], &button_rects[i]);
        }
    }
    TTF_CloseFont(font);
}

void ProjectZero::Screen::HandleEvents(SDL_Event* e, bool* quit, int* currentSelection, SDL_Window* window, SDL_Surface* surface, TTF_Font* font, const char* button_labels[]) {
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
                    DisplayLoginScreen(window, surface, font);
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

void ProjectZero::Screen::RenderButton(SDL_Surface* surface, SDL_Surface* button_surface, SDL_Rect* rect) {
    SDL_BlitSurface(button_surface, NULL, surface, rect);
}

SDL_Surface* ProjectZero::Screen::DisplayLoginScreen(SDL_Window* window, SDL_Surface* surface, TTF_Font* font) {
    SDL_Surface* login_surface_ = SDL_CreateRGBSurface(0, 1280, 720, 32, 0, 0, 0, 0);

    SDL_Color text_color = { 255, 255, 255 };
    SDL_Surface* login_text = TTF_RenderText_Solid(font, "Login Screen", text_color);
    SDL_Rect login_rect = { 100, 100, login_text->w, login_text->h };
    SDL_BlitSurface(login_text, NULL, login_surface_, &login_rect);
    SDL_FreeSurface(login_text);

    SDL_BlitSurface(login_surface_, NULL, surface, NULL);

    SDL_UpdateWindowSurface(window);

    return login_surface_;
}

void ProjectZero::Screen::Cleanup()
{
    for (auto& surface : buttonSurface_)
    {
        if (surface != nullptr)
        {
            SDL_FreeSurface(surface);
            surface = nullptr;
        }
    }

    // Freeing login surface
    if (login_surface_ != nullptr) {
        SDL_FreeSurface(login_surface_);
        login_surface_ = nullptr;
    }

    TTF_CloseFont(font_);
    font_ = nullptr;
    SDL_DestroyWindow(window_);
    window_ = nullptr;
    TTF_Quit();
    SDL_Quit();
}