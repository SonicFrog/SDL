#include <fstream>

#include "Tile.hpp"
#include "Map.hpp"
#include "Tools.hpp"
#include "ConfigurationManager.hpp"

namespace SDLRPG
{
    std::vector<std::string> Tile::tiles = std::vector<std::string>();
    SDL_Surface* Tile::tilesData = NULL;
    bool Tile::initialized = false;

    Tile::Tile(int tileNumber) : ScreenEntity(NULL)
    {
        if(!initialized)
            initializeTiles(SDLRPG_DEFAULT_TILE);
        m_tile = tileNumber;
    }

    void Tile::blit(SDL_Surface* screen) throw (DisplayRenderingException)
    {
        SDL_Rect destRect, srcRect;
        destRect.x = m_x;
        destRect.y = m_y;
        srcRect.x = SDLRPG_TILES_WIDTH * m_tile;
        srcRect.y = 0;
        SDL_BlitSurface(tilesData, &srcRect, screen, &destRect);
    }

    void Tile::initializeTiles(std::string path) throw (IOException)
    {
        ConfigurationManager cm(path);
        if(!cm.hasConfigKey(SDLRPG_TILE_CONFIG_KEY))
        {
            throw IOException(Formatter() << SDLRPG_DEFAULT_TILE << " is not a valid tile config file !");
        }
        std::string tileRoot = cm.getConfigKey(SDLRPG_TILE_CONFIG_KEY);
        tilesData = IMG_Load(tileRoot.c_str());
        if(tilesData == NULL)
        {
            throw IOException(Formatter() << tileRoot << " was not a valid image file!");
        }
        initialized = true;
    }
}
