/*
 * AIEntity.cpp
 *
 *  Created on: Dec 8, 2012
 *      Author: ars3nic
 */

#include "AIEntity.hpp"

namespace SDLRPG
{
    void AIEntity::move(int direction, int time)
    {
        GameEntity &self = *this;
        direction = 0;
        switch(proc.process(self))
        {
        case SDLRPG_DIRECTION_LEFT :
            m_x -= m_speed / time;
            break;
        }
    }
}
