#ifndef DEF_GAME_ENTITY_H
#define DEF_GAME_ENTITY_H

#include "ScreenEntity.hpp"

#define SDLRPG_DIRECTION_NONE	0
#define SDLRPG_DIRECTION_LEFT   1
#define SDLRPG_DIRECTION_RIGHT  2
#define SDLRPG_DIRECTION_UP     3
#define SDLRPG_DIRECTION_DOWN   4

#define SDLRPG_MAX_HP_DEFAULT		100
#define SDLRPG_UNDESTRUCTIBLE_HP 	-1

namespace SDLRPG
{
    /**
     * Classe representant les entites du jeu pour le moteur de gestion des collisions etc ...
     * @version 1.0
     * @author ars3nic
     * @see SDLRPG_ScreenEntity
     **/
    class GameEntity
    {
      public :
          GameEntity(ScreenEntity* screenRep);
          GameEntity(std::string name, ScreenEntity* screenRe);
          GameEntity(ScreenEntity *screenRep, ScreenEntity *destroyedRep);
          GameEntity(std::string name, ScreenEntity *screenRep, ScreenEntity *destroyedRep);
          virtual ~GameEntity();
          int getX() const;
          int getY() const;
          void update();
          void damage(int damage);
          virtual void move(int direction) = 0;
          std::string getName()  const;
          bool isDestructible() const;
          ScreenEntity* getDisplay() const;

      protected :
          GameEntity();
          ScreenEntity* m_onScreen;
          ScreenEntity* m_normalRep;
          ScreenEntity* m_destroyedRep;
          std::string m_name;
          int m_hp;
          int m_maxHP;
          int m_speed;
          int m_time;
          int m_x;
          int m_y;
          bool m_destructible;
    };
}
#endif
