#ifndef DEF_SDLRPG_TILE_HPP
#define DEF_SDLRPG_TILE_HPP

#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "ScreenEntity.hpp"

#define SDLRPG_TILE_CONFIG_KEY      "tiles.table"
#define SDLRPG_DEFAULT_TILE         "tiles.cfg"

namespace SDLRPG
{
	class Tile : public ScreenEntity
	{
        public :
            Tile(int tileNumber);
            virtual void blit(SDL_Surface* screen) throw (DisplayRenderingException);

        protected :
            int m_tile;
            static void initializeTiles(std::string path) throw (IOException);
            static void writeTiles(std::string path) throw (IOException);
            static std::vector<std::string> tiles;
            static SDL_Surface* tilesData;
            static bool initialized;
	};
}
#endif
