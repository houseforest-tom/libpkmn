/*****************************************************************
 **' IBattleScene.h
 *****************************************************************
 **' Created on: 25.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef IBATTLESCENE_H_
#define IBATTLESCENE_H_

#include "Dependencies.h"
#include "IGameObject.h"
#include "Spritebank.h"

namespace PKMN
{
	//Forward declaration
	class Battle;

	/**
	 * Represents a child scene of a pokemon battle.
	 */
	class IBattleScene : public IGameObject
	{
	private:
		/**
		 * Parent battle reference.
		 */
		Battle &m_parentBattle;

		/**
		 * Whether the scene has terminated yet.
		 */
		bool m_terminated;

	protected:
		/**
		 * Signalize to the parent battle, that this battle scene is over.
		 */
		inline void terminate(void)
		{
			m_terminated = true;
		}

	public:
		/**
		 * Construct a new child battle scene of the given parent battle.
		 *
		 * @param battle
		 * The parent battle object.
		 */
		IBattleScene(Battle &battle)
			:m_parentBattle(battle), m_terminated(false)
		{
			cout << "IBattleScene(Battle &battle)" << endl;
			NOOP;
		}

		/**
		 * @return Mutable reference to parent battle object.
		 */
		inline Battle &getParentBattle(void)
		{
			return m_parentBattle;
		}

		/**
		 * @return Whether this battle scene has terminated yet.
		 */
		inline bool terminated(void)
		{
			return m_terminated;
		}

		/**
		 * Default destructor.
		 */
		virtual ~IBattleScene(void)
		{
			cout << "~IBattleScene(void)" << endl;
			NOOP;
		}
	};
}

#endif // IBATTLESCENE_H_
