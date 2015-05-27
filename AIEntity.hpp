/*
 * AIEntity.hpp
 *
 *  Created on: Dec 8, 2012
 *      Author: ars3nic
 */

#ifndef AIENTITY_HPP_
#define AIENTITY_HPP_

#include "GameEntity.hpp"
#include "AIProcessors.hpp"

namespace SDLRPG
{
    class AIEntity : public GameEntity
    {
        public :
            AIEntity();
            AIEntity(std::string name);
            AIEntity(std::string name, int hp);
            AIEntity(int hp);
            virtual void move(int direction, int time);

        protected :
            AIProcessor &proc;
    };
}


#endif /* AIENTITY_HPP_ */
