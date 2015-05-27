#ifndef DEF_SCREENENTITY_H
#define DEF_SCREENENTITY_H

#include <SDL/SDL.h>

#include "DisplayExceptions.hpp"

namespace SDLRPG
{
    /**
     * Entite graphique du moteur de rendu
     * @version 1.0
     * @author ars3nic
     **/
    class ScreenEntity
    {
        public :
            virtual SDL_Surface* getTexture() const;
            void setTexture(SDL_Surface* texture);
            void setX(int x) throw(DisplayInvalidCoordinatesException);
            void setY(int y) throw(DisplayInvalidCoordinatesException);
            int getX() const;
            int getY() const;
            int getWidth() const;
            int getHeight() const;
            virtual void blit(SDL_Surface* screen) const throw (DisplayRenderingException);

            ScreenEntity();
            ScreenEntity(SDL_Surface* texture);
            ~ScreenEntity();

        protected :
            SDL_Surface* m_texture;
            int m_x;
            int m_y;
    };
}

#endif
