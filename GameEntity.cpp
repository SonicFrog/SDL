#include "GameEntity.hpp"
#include "ErrorPrinter.hpp"

namespace SDLRPG
{
	GameEntity::GameEntity()
	{
		m_speed = 0;
		m_destroyedRep = NULL;
		m_destructible = false;
		m_hp = -1;
		m_maxHP = 0;
		m_onScreen = NULL;
		m_normalRep = NULL;
	}

	/**
	 * Constructeur pour une entite de jeu indestructible sans nom
	 * @param screenRep
	 *      Representation de  cette entite pour le moteur graphique
	 **/
	GameEntity::GameEntity(ScreenEntity* screenRep) : m_name("")
	{
		m_onScreen = screenRep;
		m_destructible = false;
		m_normalRep = m_onScreen;
		m_destroyedRep = m_onScreen;
		m_speed = 0;
		m_hp = 1;
		m_maxHP = 0;
	}

	/**
	 * Constructeur pour une entite indestructible possedant un nom
	 * @param name
	 *      Nom de cette entite
	 * @param screenRep
	 *      Representation graphique de cette entite
	 **/
	GameEntity::GameEntity(std::string name, ScreenEntity* screenRep) : m_name(name)
	{
		m_onScreen = screenRep;
		m_normalRep = screenRep;
		m_destroyedRep = screenRep;
		m_speed = 0;
		m_hp = 0;
		m_maxHP = SDLRPG_UNDESTRUCTIBLE_HP;
		m_destructible = false;
	}

	/**
	 * Constructeur pour une entite destructible possedant un nom
	 * @param name
	 *      Nom de cette entite
	 * @param screenRep
	 *      Representation graphique de cette entite vivante
	 * @param destroyedRep
	 *      Representation de cette entite apres destruction
	 **/
	GameEntity::GameEntity(std::string name, ScreenEntity* screenRep, ScreenEntity* destroyedRep) : m_name(name)
	{
		m_onScreen = screenRep;
		m_normalRep = m_onScreen;
		m_destroyedRep = destroyedRep;
		m_destructible = true;
		m_maxHP = SDLRPG_MAX_HP_DEFAULT;
		m_hp = m_maxHP;
		m_speed = 0;
	}

	/**
	 * Constructeur pour une entite destructible sans nom
	 * @param screenRep
	 * @param destroyedRep
	 **/
	GameEntity::GameEntity(ScreenEntity *screenRep, ScreenEntity *destroyedRep) : m_name("")
	{
		m_onScreen = screenRep;
		m_normalRep = screenRep;
		m_destroyedRep = destroyedRep;
		m_destructible = true;
		m_hp = SDLRPG_UNDESTRUCTIBLE_HP;
		m_x = m_y = m_speed = 0;
		m_maxHP = SDLRPG_MAX_HP_DEFAULT;
	}

	GameEntity::~GameEntity()
	{

	}

	void GameEntity::update()
	{
		if(m_hp <= 0)
			m_onScreen = m_destroyedRep;
		else
			m_onScreen = m_normalRep;
	}

	void GameEntity::damage(int damage)
	{
		m_hp -= damage;
		if(m_hp > m_maxHP)
			m_hp = m_maxHP;
		if(m_hp < 0)
			m_hp = 0;
	}

	int GameEntity::getX() const
	{
		return m_onScreen->getX();
	}

	int GameEntity::getY() const
	{
		return m_onScreen->getY();
	}

	ScreenEntity* GameEntity::getDisplay() const
	{
		return m_onScreen;
	}

	bool GameEntity::isDestructible() const
	{
		return m_destructible;
	}
}
