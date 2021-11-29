#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <memory>
#include "./GameWindow.h"
#include "./Entity.h"
#include "./Log/Log.h"

int Run() {
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		LOG_ERROR(std::string("Could not initalize SDL2. Error: ") + SDL_GetError())
	    return 0;
	} 
	else {
		LOG_TRACE("Successfully initialized SDL2.")
	}

	if (!(IMG_Init(IMG_INIT_PNG))) {
		LOG_ERROR(std::string("Could not initalize SDL2_Image. Error: ") + SDL_GetError())
		return 0;
	}
	else {
		LOG_TRACE("Successfully initialized SDL_Image with PNG files.")
	}

	bool running = true;

	std::unique_ptr<Game::GameWindow> window = std::make_unique<Game::GameWindow>("SDL Window", 400, 400);
	LOG_INFO("Creating Window.")

    SDL_Texture* grass = window->LoadTex("res/gfx/ground_grass_1.png");
	Game::Entity grassEntity(100, 100, grass);
	
	SDL_Event e;
	while (running) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT:
					running = false;
					LOG_TRACE("SDL_QUIT event polled.")
					LOG_INFO("Application quitting.")
			}
		}

		window->Clear();
		window->Render(grassEntity, 3);
		window->Present();
	}

	SDL_Quit();

	return 0;
}