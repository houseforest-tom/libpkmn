/*****************************************************************
 **' Battle.h
 *****************************************************************
 **' Created on: 23.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef BATTLE_H_
#define BATTLE_H_

#include <memory>
#include "Party.h"
#include "IGameObject.h"
#include "EBattleType.h"
#include "IBattleScene.h"
#include "EBattleScene.h"
#include "IBattleMechanics.h"
#include "ScriptReferenceType.h"

namespace PKMN
{
	//Forward declarations
	class IGame;

	class Battle : public IGameObject, public ScriptReferenceType
	{
	private:

		/**
		 * Parent game object.
		 */
		IGame &m_parentGame;

		/**
		 * Battle mechanics to use.
		 */
		unique_ptr<IBattleMechanics> m_mechanics;

		/**
		 * Whether the battle has ended yet.
		 */
		bool m_terminated;

		/**
		 * Battle type identifier.
		 */
		EBattleType m_battleType;

		/**
		 * Current battle scene identifier.
		 */
		EBattleScene m_sceneID;

		/**
		 * Current battle scene.
		 */
		unique_ptr<IBattleScene> m_pScene;

		/**
		 * Player party.
		 */
		Party m_playerParty;

		/**
		 * Slot of currently active player pokemon.
		 */
		unsigned m_activePlayerSlot;

		/**
		 * Enemy party.
		 */
		Party m_enemyParty;

		/**
		 * Slot ot currently active enemy pokemon.
		 */
		unsigned m_activeEnemySlot;

		/**
		 * Set the current battle scene.
		 * Destroys the current scene object and allocates a new
		 * unique pointer to T, where T implements IBattleScene.
		 */
		template<typename T>
		void setBattleScene(void)
		{
			m_pScene = unique_ptr<T>(new T(*this));
		}

	public:
		/**
		 * Construct a new battle using the required information.
		 *
		 * @param game
		 * The parent game object.
		 *
		 * @param mechanics
		 * The battle mechanics to use.
		 *
		 * @param type
		 * Battle type.
		 *
		 * @param playerParty
		 * The player's pokemon team.
		 *
		 * @param enemyParty
		 * The enemy's pokemon team.
		 */
		Battle(IGame &game, IBattleMechanics *mechanics, EBattleType type, const Party &playerParty, const Party &enemyParty);

		/**
		 * Update the current battle scene.
		 *
		 * @param kb
		 * Readonly reference to keyboard state.
		 *
		 * @param mouse
		 * Readonly reference to mouse state.
		 *
		 * @param dt
		 * Time in seconds passed since last frame.
		 */
		virtual void update(const Keyboard &kb, const Mouse &mouse, float dt) override;

		/**
		 * Render the current battle scene.
		 *
		 * @param window
		 * Reference to render window to use.
		 */
		virtual void render(RenderWindow &window);

		/**
		 * @return Parent game object.
		 */
		inline IGame &getParentGame(void)
		{
			return m_parentGame;
		}

		/**
		 * @return Readonly reference to battle mechanics used.
		 */
		inline IBattleMechanics &getBattleMechanics(void)
		{
			return *m_mechanics.get();
		}

		/**
		 * @return Mutable reference to player pokemon party.
		 */
		inline Party &getPlayerParty(void)
		{
			return m_playerParty;
		}

		/**
		 * @return Readonly reference to player pokemon party.
		 */
		inline const Party &getPlayerParty(void) const
		{
			return m_playerParty;
		}

		/**
		 * @return Mutable reference to currently active player pokemon.
		 */
		inline Pokemon &getActivePlayerPokemon(void)
		{
			return m_playerParty[m_activePlayerSlot];
		}

		/**
		 * @return Readonly reference to currently active player pokemon.
		 */
		inline const Pokemon &getActivePlayerPokemon(void) const
		{
			return m_playerParty[m_activePlayerSlot];
		}

		/**
		 * @return Mutable reference to enemy pokemon party.
		 */
		inline Party &getEnemyParty(void)
		{
			return m_enemyParty;
		}

		/**
		 * @return Readonly reference to enemy pokemon party.
		 */
		inline const Party &getEnemyParty(void) const
		{
			return m_enemyParty;
		}

		/**
		 * @return Mutable reference to currently active enemy pokemon.
		 */
		inline Pokemon &getActiveEnemyPokemon(void)
		{
			return m_enemyParty[m_activeEnemySlot];
		}

		/**
		 * @return Readonly reference to currently active enemy pokemon.
		 */
		inline const Pokemon &getActiveEnemyPokemon(void) const
		{
			return m_enemyParty[m_activeEnemySlot];
		}

		/**
		 * @return Type of this battle.
		 */
		inline EBattleType getBattleType(void) const
		{
			return m_battleType;
		}

		/**
		 * @return Whether the current battle has ended yet.
		 */
		inline bool terminated(void) const
		{
			return m_terminated;
		}

		/**
		 * Signalize that this battle has ended.
		 */
		inline void terminate(void)
		{
			m_terminated = true;
			m_pScene.reset(nullptr);
		}

		/**
		 * Default destructor.
		 */
		virtual ~Battle(void)
		{
			cout << "~Battle(void)" << endl;
			NOOP;
		}
	};
}

#endif // BATTLE_H_
