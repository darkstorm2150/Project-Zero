#include "screen.h"
#include <iostream>
#include <stdexcept>

ProjectZero::Screen::Screen(int width, int height) :
    window_(nullptr, SDL_DestroyWindow),
    surface_(nullptr, SDL_FreeSurface),
    font_(nullptr, TTF_CloseFont),
    currentSelection_(0),
    screenState_(ScreenState::RUNNING)
{
    buttonLabels_ = { "Login", "Register", "Exit", "Help" };
}

ProjectZero::Screen::~Screen() = default;

bool ProjectZero::Screen::Initialize() {
    try {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            throw std::runtime_error("SDL Initialize failed: " + std::string(SDL_GetError()));
        }
            
        // Initialize SDL_ttf
        if (TTF_Init() < 0) {
            throw std::runtime_error("SDL_ttf Initialize failed: " + std::string(TTF_GetError()));
        }
            
        window_.reset(SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN));
        if (!window_)
        {
            throw std::runtime_error("Window creation failed: " + std::string(SDL_GetError()));
        }

        surface_.reset(SDL_GetWindowSurface(window_.get()));
        if (!surface_)
        {
            throw std::runtime_error("Surface creation failed: " + std::string(SDL_GetError()));
        }

        font_.reset(TTF_OpenFont("8bit16.ttf", 48));
        if (!font_)
        {
            throw std::runtime_error("TTF Font loading failed: " + std::string(TTF_GetError()));
        }

        CreateButtons();
    } 
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}

void ProjectZero::Screen::CreateButtons()
{
    SDL_Color buttonColors = { 255, 255, 255 };

    for (size_t i = 0; i < buttonLabels_.size(); i++)
    {
        SDL_Surface* buttonSurface = TTF_RenderText_Solid(font_.get(), buttonLabels_[i].c_str(), buttonColors);
        if (!buttonSurface) {
            throw std::runtime_error("Failed to render text: " + std::string(TTF_GetError()));
        }
        SDL_Rect buttonRect = {
            (1280 - buttonSurface->w) / 2, 
            200 + static_cast<int>(i) * 70,
            buttonSurface->w, 
            buttonSurface->h 
        };

        buttonTextures_.emplace_back(buttonSurface, SDL_FreeSurface);
        buttonRects_.push_back(buttonRect);
    }
}

void ProjectZero::Screen::RenderLogin() const {
    SDL_FillRect(surface_.get(), nullptr, SDL_MapRGB(surface_->format,
        0, 0, 0));

    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface* loginText = TTF_RenderText_Solid(font_.get(), "Login Screen", textColor);
        if (!loginText) {
            throw std::runtime_error("Failed to render login text: " +
                std::string(TTF_GetError()));
        }
        SDL_Rect loginRect = { (1280 - loginText->w) / 2, 100, loginText->w, loginText->h };
        SDL_BlitSurface(loginText, nullptr, surface_.get(), &loginRect);
        SDL_FreeSurface(loginText);
}

void ProjectZero::Screen::RunEventLoop()
{
    SDL_Event e;
    while (screenState_ != ScreenState::QUITTING) {
        switch (screenState_) {
            case ScreenState::RUNNING:
                RenderMenu();
                break;
            case ScreenState::LOGIN:
                RenderLogin();
                break;
        }
        SDL_UpdateWindowSurface(window_.get());
        while (SDL_PollEvent(&e) != 0) {
            HandleEvents(&e);
        }
    }
}

void ProjectZero::Screen::RenderMenu() const
{
    SDL_FillRect(surface_.get(), NULL, SDL_MapRGB(surface_->format, 0, 0, 0));

    for (size_t i = 0; i < buttonTextures_.size(); i++)
    {
        if (i == currentSelection_)
        {
            SDL_Color highlightColor = { 255, 255, 0 };
            SDL_Surface* highlightedButton = TTF_RenderText_Solid(font_.get(), buttonLabels_[i].c_str(), highlightColor);
            if (!highlightedButton) {
                throw std::runtime_error("Failed to render highlighted button text: " + std::string(TTF_GetError()));
            }
            SDL_Rect highlightedRect = buttonRects_[i];
            highlightedRect.x = (1280 - highlightedButton->w) / 2;
            highlightedRect.w = highlightedButton->w;
            highlightedRect.h = highlightedButton->h;
            

            SDL_BlitSurface(highlightedButton, nullptr, surface_.get(), &highlightedRect);
            SDL_FreeSurface(highlightedButton);
        }
        else
        {
            SDL_Rect buttonRect = buttonRects_[i]; // Create a non-const copy
            SDL_BlitSurface(buttonTextures_[i].get(), nullptr, surface_.get(), &buttonRect);
        }
    }
}

void ProjectZero::Screen::HandleEvents(SDL_Event* e) {
    if (e->type == SDL_QUIT) {
        screenState_ = ScreenState::QUITTING;
    }
    else if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
        case SDLK_ESCAPE:
            if (screenState_ == ScreenState::LOGIN)
                screenState_ = ScreenState::RUNNING;
            break;

        case SDLK_UP:
            if (screenState_ == ScreenState::RUNNING)
                currentSelection_ = (currentSelection_ - 1 + buttonTextures_.size()) % buttonTextures_.size();
            break;

        case SDLK_DOWN:
            if (screenState_ == ScreenState::RUNNING)
                currentSelection_ = (currentSelection_ + 1) % buttonTextures_.size();
            break;

        case SDLK_RETURN:
            if (screenState_ == ScreenState::RUNNING) {
                switch (currentSelection_) {
                case 0: DisplayLoginScreen(); break;
                case 1: /* Register */ break;
                case 2: screenState_ = ScreenState::QUITTING; break;
                case 3: /* Help */ break;
                default: [[fallthrough]];
                }
            }
            break;

        default: break;
        }
    }
}

void ProjectZero::Screen::DisplayLoginScreen()
{
    screenState_ = ScreenState::LOGIN;
    SDL_Surface* loginSurface = SDL_CreateRGBSurface(0, 1280, 720, 32, 0, 0, 0, 0);
    if (!loginSurface) {
        throw std::runtime_error("Failed to create login surface: " + std::string(SDL_GetError()));
    }

    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface* loginText = TTF_RenderText_Solid(font_.get(), "Login Screen", textColor);
    if (!loginText) {
        SDL_FreeSurface(loginSurface);
        throw std::runtime_error("Failed to render login text: " + std::string(TTF_GetError()));
    }
    SDL_Rect loginRect = { 100, 100, loginText->w, loginText->h };
    SDL_BlitSurface(loginText, NULL, loginSurface, &loginRect);
    SDL_FreeSurface(loginText);

    SDL_BlitSurface(loginSurface, NULL, surface_.get(), NULL);

    SDL_UpdateWindowSurface(window_.get());

    SDL_FreeSurface(loginSurface);
}

void ProjectZero::Screen::Cleanup()
{
    // No need to manually free resources, unique_ptr will handle it
}