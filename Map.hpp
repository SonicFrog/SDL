#ifndef DEF_MAP_HPP
#define DEF_MAP_HPP

#include <vector>

#include "ScreenEntity.hpp"
#include "Tile.hpp"

namespace SDLRPG
{
#define SDLRPG_TILES_WIDTH  24
#define SDLRPG_TILES_HEIGHT 24

#define SDLRPG_TILE_Y       13
#define SDLRPG_TILE_X       15

#define SDLRPG_MAX_Y        50
#define SDLRPG_MAX_X        2500

	class Map : public ScreenEntity
	{
		public :
            Map(std::string mapFile) throw (IOException);
			virtual void blit(SDL_Surface* screen) const throw (DisplayRenderingException);
			virtual SDL_Surface* getTexture() const;

		protected :
			std::vector<Tile*> m_tiles;

			void renderMap(int x, int y, SDL_Surface* screen) const;
	};
}
#endif
