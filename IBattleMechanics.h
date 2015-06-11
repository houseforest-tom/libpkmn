/*****************************************************************
 **' IBattleMechanics.h
 *****************************************************************
 **' Created on: 24.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef IBATTLEMECHANICS_H_
#define IBATTLEMECHANICS_H_

#include "Dependencies.h"
#include "Database.h"

namespace PKMN
{
	//Forward declaration
	class IGame;

	/**
	 * Possible battle turn orders.
	 */
	enum class ETurnOrder : uint8_t
	{
		PLAYER_FIRST,  //!< Player goes first
		OPPONENT_FIRST //!< Opponent goes first
	};

	/**
	 * Derivations of this interface describe how battle mechanics are to be handled.
	 * This includes determination of turn order, accuracy checks, critical hit checks,
	 * damage calculation and the activation of secondary effects, etc.
	 */
	class IBattleMechanics
	{
	private:

		/**
		 * Parent game object.
		 */
		IGame &m_parentGame;

	public:

		/**
		 * Construct a new battle mechanics object.
		 *
		 * @param game
		 * Parent game object.
		 */
		IBattleMechanics(IGame &game)
			:m_parentGame(game)
		{
			NOOP;
		}

		/**
		 * @return Mutable reference to parent game.
		 */
		IGame &getParentGame(void);

		/**
		 * Determine the turn order after both players have chosen their next action.
		 *
		 * @return
		 * Resulting turn order.
		 */
		virtual ETurnOrder determineTurnOrder(void) = 0;

		/**
		 * Determine whether a casted move will hit.
		 *
		 * @param moveID
		 * ID of move used.
		 *
		 * @return
		 * True <=> move hits, False <=> move misses.
		 */
		virtual bool willMoveHit(MoveID moveID) = 0;

		/**
		 * Determine whether a casted move will hit critically.
		 *
		 * @param moveID
		 * ID of move used.
		 *
		 * @return
		 * True <=> move hits, False <=> move misses.
		 */
		virtual bool willMoveHitCritically(MoveID moveID) = 0;

		/**
		 * Determine the damage a move will inflict on the opponent.
		 *
		 * @param moveID
		 * ID of the move used.
		 *
		 * @param crit
		 * Whether or not the move hit critically.
		 *
		 * @return
		 * The damage the move will inflict.
		 */
		virtual uint16_t determineMoveDamage(MoveID moveID, bool crit) = 0;

		/**
		 * Determine whether a thrown ball will catch the opposing pokemon.
		 *
		 * @param ballID
		 * ID of ball used.
		 *
		 * @return
		 * True <=> will catch, False <=> won't catch.
		 */
		virtual bool willBallCatch(unsigned ballID) = 0;

		/**
		 * Determine whether the player's attempt to run from battle
		 * will be successful.
		 *
		 * @return
		 * True <=> success, False <=> failure.
		 */
		virtual bool willRunSucceed(void) = 0;

		/**
		 * Default destructor.
		 */
		virtual ~IBattleMechanics(void)
		{
			NOOP;
		}
	};
}



#endif // IBATTLEMECHANICS_H_
