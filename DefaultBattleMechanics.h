/*****************************************************************
 **' DefaultBattleMechanics.h
 *****************************************************************
 **' Created on: 24.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef DEFAULTBATTLEMECHANICS_H_
#define DEFAULTBATTLEMECHANICS_H_

#include <IBattleMechanics.h>

namespace PKMN
{
	class DefaultBattleMechanics : public IBattleMechanics
	{
	public:

		/**
		 * Construct a new default battle mechanics object.
		 *
		 * @param game
		 * Parent game object.
		 */
		DefaultBattleMechanics(IGame &game);

		/**
		 * Determine who goes first this turn.
		 *
		 * @return
		 * Turn order.
		 */
		ETurnOrder determineTurnOrder(void) override;

		/**
		 * Determine whether a casted move will hit.
		 *
		 * @param moveID
		 * ID of the move used.
		 *
		 * @return
		 * Whether the move will hit.
		 */
		bool willMoveHit(MoveID moveID) override;

		/**
		 * Determine whether a casted move will hit critically.
		 *
		 * @param moveID
		 * ID of the move used.
		 *
		 * @return Whether the move will hit critically.
		 */
		bool willMoveHitCritically(MoveID moveID) override;

		/**
		 * Determine the amount of damage a move will inflict.
		 *
		 * @param moveID
		 * ID of the move used.
		 *
		 * @param crit
		 * Whether the hit was critical.
		 *
		 * @return
		 * The damage that the move will inflict.
		 */
		uint16_t determineMoveDamage(MoveID moveID, bool crit) override;

		/**
		 * Determine whether a thrown ball will catch.
		 *
		 * @param ballID
		 * ID of the ball used.
		 *
		 * @return
		 * Whether the bal will catch.
		 */
		bool willBallCatch(unsigned ballID) override;

		/**
		 * Determine whether a run attempt will succeed.
		 *
		 * @return
		 * Whether the run attempt succeeds.
		 */
		bool willRunSucceed(void) override;
	};
}

#endif // DEFAULTBATTLEMECHANICS_H_
