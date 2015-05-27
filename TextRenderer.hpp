#ifndef DEF_TEXT_RENDERER_H
#define DEF_TEXT_RENDERER_H

#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "DisplayExceptions.hpp"

#ifdef DEF_SDLRPG_DEBUG
#include "tests/TextRendererTest.hpp"
#endif

#define SDLRPG_TEXT_DEFAULT_FONT    "comic.ttf"
#define SDLRPG_TEXT_DEFAULT_COLOR   {0, 0, 0, 0}
#define SDLRPG_TEXT_DEFAULT_SIZE    32

namespace SDLRPG
{
	/**
	 * Classe pour le rendu de texte a l'ecran
	 * @version 1.0
	 * @author ars3nic
	 **/
	class TextRenderer
	{
	  public :
		TextRenderer() throw (DisplayTextRenderingException);
		TextRenderer(std::string policeName) throw (DisplayTextRenderingException);
		TextRenderer(std::string policeName, SDL_Color color) throw (DisplayTextRenderingException);
		TextRenderer(std::string policeName, SDL_Color color, int size) throw (DisplayTextRenderingException);
		~TextRenderer();

		void init(std::string fontName, SDL_Color color, int size) throw (DisplayTextRenderingException);

		SDL_Surface* renderText(std::string text) throw (DisplayTextRenderingException);
		SDL_Surface* renderText(std::string text, SDL_Color color) throw (DisplayTextRenderingException);
		SDL_Surface* renderText(std::string text, TTF_Font* font) throw (DisplayTextRenderingException);
		SDL_Surface* renderText(std::string text, TTF_Font* font, SDL_Color color) throw (DisplayTextRenderingException);

	  protected :
		TTF_Font* m_font;
		SDL_Color m_color;
		int m_size;

		#ifdef DEF_SDLRPG_DEBUG
		friend void TextRendererTest::instantiateTest();
		#endif
	};
}

#endif
