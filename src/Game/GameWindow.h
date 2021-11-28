#pragma once


#include "SDL.h"
#include "SDL_image.h"
#include <string>

namespace Game {
	class GameWindow {
	public:
		GameWindow(const std::string& title, int width, int height);

		void Dispose();
		void Clear();
		void RenderTexture(SDL_Texture* tex);
		void Present();
		SDL_Texture* LoadTex(std::string path);
	private:
		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;
	};
}