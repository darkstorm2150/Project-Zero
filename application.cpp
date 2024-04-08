#include "application.hpp"

SDL_Surface* load_surface(char const* path)
{
	SDL_Surface* image_surface = SDL_LoadBMP(path);

	if (!image_surface)
		return 0;

	return image_surface;
}

Application::Application()
{
	m_window = SDL_CreateWindow("SDL2 Window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		680, 480,
		0);

	if (!m_window)
	{
		std::cout << "Failed to create window\n";
		std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
		return;
	}

	m_window_surface = SDL_GetWindowSurface(m_window);

	if (!m_window_surface)
	{
		std::cout << "Failed to get window's surface\n";
		std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
		return;
	}

	m_image = load_surface("zendaya.bmp");
	SDL_BlitSurface(m_image, NULL, m_window_surface, NULL);

}

Application::~Application()
{
	SDL_FreeSurface(m_window_surface);
	SDL_DestroyWindow(m_window);
}

void Application::update()
{
	bool keep_window_open = true;
	while (keep_window_open)
	{
		while (SDL_PollEvent(&m_window_event) > 0)
		{
			switch (m_window_event.type)
			{
			case SDL_QUIT:
				keep_window_open = false;
				break;
			}
		}

		draw();
	}
}

void Application::draw()
{
	SDL_UpdateWindowSurface(m_window);
}