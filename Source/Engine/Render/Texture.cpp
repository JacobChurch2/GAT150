#include "Texture.h"
#include "SDL2-2.28.0/include/SDL_image.h"
#include "Core/Logger.h"
#include "Render.h"

namespace kda {

	Texture::~Texture()
	{
		if (m_texture) SDL_DestroyTexture(m_texture);
	}


	bool Texture::Load(const std::string& filename, Renderer& renderer ){
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface)
		{
			WARNING_LOG("Surface missing");
			return false;
		}
		
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);

		SDL_FreeSurface(surface);
		if (!m_texture)
		{
			WARNING_LOG("Texture missing");
			return false;
		}
		return true;
	}

	vec2 Texture::GetSize(){
		ASSERT_LOG(m_texture, "Texture is null");
		SDL_Point point;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &point.x, &point.y);
		return vec2{ point.x, point.y };
	}

	bool Texture::Create(std::string filename, ...){
		va_list args;
		va_start(args, filename);
		Renderer& renderer = va_arg(args, Renderer);
		va_end(args);	
		return Load(filename, renderer);
	}

}
