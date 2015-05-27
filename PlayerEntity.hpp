/*
 * PlayerEntity.hpp
 *
 *  Created on: Dec 8, 2012
 *      Author: ars3nic
 */

#ifndef PLAYERENTITY_HPP_
#define PLAYERENTITY_HPP_

#include "GameEntity.hpp"

namespace SDLRPG
{
	class PlayerEntity : GameEntity
	{
		public :

		private :
			virtual void move(int direction);
	};
}

#endif /* PLAYERENTITY_HPP_ */
