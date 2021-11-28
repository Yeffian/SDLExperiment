#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "./Log/Log.h"
#include "GameWindow.h"
#include <string>
#include <iostream>


namespace Game {
	GameWindow::GameWindow(const std::string& title, int width, int height) : m_Window(nullptr), m_Renderer(nullptr) {
		m_Window = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			SDL_WINDOW_SHOWN
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

	void GameWindow::Dispose() {
		LOG_TRACE("Disposing GameWindow");

		SDL_DestroyRenderer(m_Renderer);
		SDL_DestroyWindow(m_Window);
	}

	void GameWindow::Clear() {
		SDL_RenderClear(m_Renderer);
	}

	void GameWindow::RenderTexture(SDL_Texture* tex) {
		SDL_RenderCopy(m_Renderer, tex, nullptr, nullptr);
	}

	void GameWindow::Present() {
		SDL_RenderPresent(m_Renderer);
	}
}