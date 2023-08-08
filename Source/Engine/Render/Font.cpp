#include "Font.h"
#include <SDL2-2.28.0/include/SDL_ttf.h>
#include <Core/Logger.h>
namespace kda{

	Font::Font(const std::string& filename, int fontSize){
		Load(filename, fontSize);
		//<call Load(filename, fontSize) to load and create font>
	}

	Font::~Font(){
		if (m_ttfFont) {
			Font(TTF_CloseFont);
		}
		//<if m_ttfFont not null, close font(TTF_CloseFont)>
	}

	bool Font::Create(std::string filename, ...) {
		va_list args;
		va_start(args, filename);
		int fontSize = va_arg(args, int);
		va_end(args);
		return Load(filename, fontSize);
	}

	bool Font::Load(const std::string& filename, int fontSize){
		//<call TTF_OpenFont>
			//<use filename.c_str() to get the c - style string>
			//<assign the return value of TTF_OpenFont to m_ttfFont>

		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);
		if (m_ttfFont == nullptr) {
			WARNING_LOG("Failed to open font: " << filename);
			return false;
		}
		return true;
	}
}
