#pragma once
#include <iostream>
#include <SDL3/SDL.h>

namespace viper {
	class Renderer
	{
	public:
		Renderer() = default;

		bool Initialize();
		void Shutdown();
		bool CreateWinow(const std::string& name, int width, int height);

		void Clear();
		void Present();

		void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawPoint(float x, float y);
	private:
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;

	};
}


