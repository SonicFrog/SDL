#ifndef DEF_DISPLAY_ENGINE_H
#define DEF_DISPLAY_ENGINE_H

#include <iostream>
#include <exception>
#include <string>
#include <map>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "ScreenEntity.hpp"
#include "TextRenderer.hpp"
#include "DisplayExceptions.hpp"

#ifdef DEF_SDLRPG_DEBUG
#include "tests/DisplayEngineTest.hpp"
#endif

#define SDLRPG_DEFAULT_FLAGS            SDL_INIT_VIDEO | SDL_INIT_AUDIO
#define SDLRPG_DEFAULT_WIDTH            800
#define SDLRPG_DEFAULT_HEIGHT           600
#define SDLRPG_DEFAULT_COLOR            32
#define SDLRPG_DEFAULT_RENDERER         SDL_HWSURFACE
#define SDLRPG_DEFAULT_SCREEN_FLAGS     SDLRPG_DEFAULT_RENDERER | SDL_DOUBLEBUF | SDL_ASYNCBLIT

#define SDLRPG_DISPLAY_ENGINE_VERSION   "0.1"
#define SDLRPG_DISPLAY_ENGINE_NAME      "Aurora"

#define SDLRPG_DISPLAY_ENGINE_ICON      "sprites/icon.jpg"

namespace SDLRPG
{
	typedef int ScreenEntityID;

	/**
	 * Moteur graphique de SDLRPG
	 * @version 1.0
	 * @author ars3nic
	 **/
	class DisplayEngine
	{
		public :
			ScreenEntityID registerEntity(ScreenEntity* entity);
			void drawEntity(ScreenEntityID id, int x, int y);
			void drawEntity(ScreenEntityID id, int x, int y, bool center);
			void moveEntity(ScreenEntityID id, int xmove, int ymove);
			void eraseEntity(ScreenEntityID id);
			void setBackground(ScreenEntity* bTexture);
			void clearScreen() throw (DisplayRenderingException);
			void updateScreen();
			void resizeScreen(int w, int h) throw (DisplayRenderingException, DisplayInitException);
			void printInfo() const;
			bool hasAcceleration() const;

			void saveEngineState();
			void restoreEngineState();

            SDL_Rect& getSize() const;
			int getWidth() const;
			int getHeight() const;
			SDL_PixelFormat* getFormat() const;

			ScreenEntityID renderText(std::string text);
			ScreenEntityID renderText(std::string text, SDL_Color color);
			ScreenEntityID renderText(std::string text, TTF_Font* font);
			ScreenEntityID renderText(std::string text, TTF_Font* font, SDL_Color color);

			DisplayEngine();
			DisplayEngine(Uint32 flags);
			DisplayEngine(Uint32 flags, int width, int height, int bit, Uint32 screenFlags);
			~DisplayEngine();

		protected :
			unsigned int m_LastID;
			SDL_Rect m_size;
			SDL_Surface* m_screen;
			ScreenEntity* m_background;
			std::string m_version;

			std::map<int, ScreenEntity*> m_EntityList;
			std::map<int, ScreenEntity*> m_ScreenList;

			std::map<int, ScreenEntity*> m_stateList;

			TextRenderer* m_renderer;

			std::string getVersion() const;
			void init(Uint32 flags) throw (DisplayInitException);
			void loadScreen(int width, int height, int bit, Uint32 flags) throw (DisplayInitException);
			void blitSurfaces();
			void checkScreen() const throw (DisplayRenderingException);

			#ifdef DEF_SDLRPG_DEBUG
			friend class DisplayTest;
			#endif
	};
}

#endif
