/*
 * PlayerEntity.cpp
 *
 *  Created on: Dec 8, 2012
 *      Author: ars3nic
 */

#include "PlayerEntity.hpp"
#include "ErrorPrinter.hpp"

namespace SDLRPG
{
	/**
	 * Deplace l'entite dans la direction selectionne
	 * @see SDLRPG_ScreenEntity#setY
	 * @see SDLRPG_ScreenEntity#setX
	 **/
	void PlayerEntity::move(int direction)
	{
		int delay = SDL_GetTicks() - m_time;
		switch(direction)
		{
		case SDLRPG_DIRECTION_DOWN :
			m_onScreen->setX(m_onScreen->getX() + m_speed / delay);
			break;

		case SDLRPG_DIRECTION_LEFT :
			m_onScreen->setY(m_onScreen->getY() - m_speed / delay);
			break;

		case SDLRPG_DIRECTION_RIGHT :
			m_onScreen->setY(m_onScreen->getY() + m_speed / delay);
			break;

		case SDLRPG_DIRECTION_UP :
			m_onScreen->setX(m_onScreen->getX() - m_speed / delay);
			break;

		case SDLRPG_DIRECTION_NONE :
			break;
		default:
			ErrorPrinter::printInternalError("Invalid direction code " + direction);
			throw GameException("Invalid direction code " + direction);
		}
	}
}
