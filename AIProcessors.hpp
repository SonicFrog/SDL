#ifndef DEF_AIPROCESSORS_HPP
#define DEF_AIPROCESSORS_HPP

#include "GameEntity.hpp"

namespace SDLRPG
{
    class AIProcessor
    {
        public :
            virtual int process(const GameEntity& self) = 0;
            virtual ~AIProcessor();
    };


    class EnemyAIProcessor : public AIProcessor
    {
        public :
            EnemyAIProcessor(const GameEntity& player);
            virtual int process(const GameEntity& self);

        protected :
            const GameEntity* m_player;
    };
}

#endif
