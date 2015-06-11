/*****************************************************************
 **' Battle.cpp
 *****************************************************************
 **' Created on: 24.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include <Battle.h>
#include <IGame.h>
#include <InitBattleScene.h>

namespace PKMN
{
	Battle::Battle(IGame &game, IBattleMechanics *mechanics, EBattleType type, const Party &playerParty, const Party &enemyParty)
		:m_parentGame(game), m_terminated(false), m_battleType(type), m_playerParty(playerParty),
		 m_activePlayerSlot(0), m_enemyParty(enemyParty), m_activeEnemySlot(0)
	{
		cout << "Battle(IBattleMechanics *mechanics, EBattleType type, ...)" << endl;
		m_mechanics.reset(mechanics);
		m_sceneID = EBattleScene::INIT;
		setBattleScene<InitBattleScene>();
	}

	/*****************************************************************
	 *****************************************************************/

	void Battle::update(const Keyboard &kb, const Mouse &mouse, float dt)
	{
		if(!m_pScene->terminated())
		{
			m_pScene->update(kb, mouse, dt);
		}
		else
		{
			//Change scene depending on current scene ID
			switch(m_sceneID)
			{
				case EBattleScene::INIT: terminate(); break;
				default: break;
			}
		}
	}

	/*****************************************************************
	 *****************************************************************/

	void Battle::render(RenderWindow &window)
	{
		m_pScene->render(window);
	}
}
