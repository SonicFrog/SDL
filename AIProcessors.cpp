#include "AIProcessors.hpp"

namespace SDLRPG
{
    AIProcessor::~AIProcessor()
    {

    }

    int EnemyAIProcessor::process(const GameEntity& self)
    {
        int out = SDLRPG_DIRECTION_NONE;
        if(self.getX() < m_player->getX()) {
            out = SDLRPG_DIRECTION_RIGHT;
        } else {
            out = SDLRPG_DIRECTION_LEFT;
        }
        return out;
    }

    EnemyAIProcessor::EnemyAIProcessor(const GameEntity& player)
    {
        m_player = &player;
    }
}
