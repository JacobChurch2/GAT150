
#pragma once
#include <string>
#include <../ThirdParty/SDL2-2.28.0/include/SDL.h>
namespace kda
{

	class Renderer 
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		bool Initialize();
		void Shutdown();

		void CreateWindow(const std::string& title, int width, int height);
		void BeginFrame();
		void EndFrame();

		void SetColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A);
		void DrawLine(int x1, int y1, int x2, int y2);
		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawPoint(int x1, int y1);
		void DrawPoint(float x1, float y1);

		void DrawTexture(class Texture* texture, float x, float y, float angle = 0.0f);

		int getWidth() const { return m_width; }
		int getHeight() const { return m_height; }

		friend class Text;
		friend class Texture;
	private:
		int m_width = 0;
		int m_height = 0;

		SDL_Renderer* m_renderer = nullptr;
		SDL_Window* m_window = nullptr;
	};

	extern Renderer g_renderer;
}