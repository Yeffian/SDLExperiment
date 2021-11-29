#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "./Log/Log.h"
#include "GameWindow.h"
#include <string>
#include <iostream>


namespace Game {
	GameWindow::GameWindow(const std::string& title, int width, int height) : m_Window(nullptr), m_Renderer(nullptr) {
		const auto winFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;

		m_Window = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			winFlags
		);

		if (m_Window == nullptr) {
			std::cout << "Error Initializing Window, Error: " << SDL_GetError() << std::endl;
		}

		m_Renderer = SDL_CreateRenderer(
			m_Window,
			-1,
			SDL_RENDERER_ACCELERATED
		);
	}

	SDL_Texture* GameWindow::LoadTex(std::string path) {
		SDL_Texture* texture = nullptr;

		texture = IMG_LoadTexture(m_Renderer, path.c_str());

		if (texture == nullptr)
			LOG_ERROR(std::string("Unable to load texture. Error: ") + IMG_GetError())
		else
			return texture;
	}

	GameWindow::~GameWindow() {
		LOG_TRACE("Disposing GameWindow");

		SDL_DestroyRenderer(m_Renderer);
		SDL_DestroyWindow(m_Window);
	}

	void GameWindow::Clear() {
		SDL_RenderClear(m_Renderer);
	}

	void GameWindow::Render(Entity& entity, int scaler)
	{
		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = 32;
		src.h = 32;

		SDL_Rect dst;
		dst.x = entity.GetX() * scaler;
		dst.y = entity.GetY() * scaler;
		dst.w = 32 * scaler;
		dst.h = 32 * scaler;


		SDL_RenderCopy(m_Renderer, entity.GetTexture(), &src, &dst);
	}

	void GameWindow::Present() {
		SDL_RenderPresent(m_Renderer);
	}
}