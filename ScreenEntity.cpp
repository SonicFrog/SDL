#include "ScreenEntity.hpp"
#include "ErrorPrinter.hpp"
#include "Tools.hpp"

namespace SDLRPG
{
	ScreenEntity::ScreenEntity(SDL_Surface* texture)
	{
		m_texture = texture;
		m_x = 0;
		m_y = 0;
	}

	ScreenEntity::~ScreenEntity()
	{
	    if(m_texture != NULL)
            SDL_FreeSurface(m_texture);
	}

	SDL_Surface* ScreenEntity::getTexture() const
	{
		return m_texture;
	}

	void ScreenEntity::blit(SDL_Surface* screen) const throw (DisplayRenderingException)
	{
		if(screen == NULL || m_texture == NULL)
		{
			throw DisplayRenderingException("No screen to blit surface on!");
		}
		SDL_Rect pos;
		pos.x = m_x;
		pos.y = m_y;
		SDL_BlitSurface(m_texture, NULL, screen, &pos);
	}

	void ScreenEntity::setTexture(SDL_Surface* texture)
	{
		if(texture == NULL)
		{
			ErrorPrinter::printDisplayWarning("Setting entity's texture to null");
		}
		m_texture = texture;
	}

	void ScreenEntity::setX(int x) throw(DisplayInvalidCoordinatesException)
	{
		if(x < 0)
			throw DisplayInvalidCoordinatesException(Formatter() << "(" << x << ", " << m_y << ")");
		m_x = x;
	}


	void ScreenEntity::setY(int y) throw(DisplayInvalidCoordinatesException)
	{
		if(y < 0)
			throw DisplayInvalidCoordinatesException(Formatter() << "(" << m_x << ", " << y << ")");
		m_y = y;
	}

	int ScreenEntity::getX() const
	{
		return m_x;
	}

	int ScreenEntity::getY() const
	{
		return m_y;
	}

	int ScreenEntity::getWidth() const
	{
		return m_texture->w;
	}

	int ScreenEntity::getHeight() const
	{
		return m_texture->h;
	}
}
