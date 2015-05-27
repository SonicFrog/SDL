#include "Map.hpp"

namespace SDLRPG
{
    Map::Map(std::string mapFile) throw (IOException) : ScreenEntity(NULL)
    {

    }

	void Map::blit(SDL_Surface* screen) const throw (DisplayRenderingException)
	{
		if(screen == NULL)
			throw DisplayRenderingException("No screen loaded");
		renderMap(m_x, m_y, screen);
	}

	SDL_Surface* Map::getTexture() const
	{
		return (SDL_Surface *) 1;
	}

	void Map::renderMap(int x, int y, SDL_Surface* screen) const
	{
		SDL_Rect player_loc;
		SDL_Rect draw_start;

		player_loc.x = x / SDLRPG_TILES_WIDTH;
		player_loc.y = y / SDLRPG_TILES_HEIGHT;

		draw_start.x = player_loc.x - SDLRPG_TILE_X / 2;
		draw_start.y = player_loc.y - SDLRPG_TILE_Y / 2;

		for(int i = draw_start.x ; i < SDLRPG_TILE_X ; i++)
		{
			for(int j = draw_start.y ; j < SDLRPG_TILE_Y ; j++)
			{
				;
			}
		}
	}
}
