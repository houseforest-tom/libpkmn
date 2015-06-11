/*****************************************************************
 **' MoveEffect.h
 *****************************************************************
 **' Created on: 17.05.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef MOVEEFFECT_H_
#define MOVEEFFECT_H_

#include <Dependencies.h>
#include <angelscript.h>

namespace PKMN
{
	//Forward declarations
	class ScriptInterface;
	class Pokemon;

	using AngelscriptModuleID  = unsigned;
	using AngelscriptContextID = unsigned;

	/**
	 * ID types.
	 */
	typedef uint16_t MoveID;
	typedef uint16_t MoveEffectID;

	class MoveEffect
	{

	private:

		/**
		 * Move effect ID.
		 */
		MoveEffectID m_ID;

		/**
		 * Script module ID.
		 */
		AngelscriptModuleID m_scriptModuleID;

		/**
		 * Script context ID.
		 */
		AngelscriptContextID m_scriptContextID;

		/**
		 * Script interface reference.
		 */
		ScriptInterface &m_scriptIF;

	public:

		/**
		 * Construct a new move effect and load its code from file.
		 *
		 * @param id
		 * Effect ID.
		 *
		 * @param scriptIF
		 * Script interface.
		 */
		MoveEffect(MoveEffectID id, ScriptInterface &scriptIF);

		/**
		 * @return Move effect ID.
		 */
		inline MoveEffectID getID(void) const
		{
			return m_ID;
		}

		/**
		 * Determine the damage done by the move.
		 *
		 * @param caster
		 * The casting pokemon.
		 *
		 * @param target
		 * The pokemon targeted by the move.
		 *
		 * @param moveID
		 * ID of the move used.
		 *
		 * @param initial
		 * The intially calculated move damage.
		 *
		 * @param crit
		 * Whether the move hit critically.
		 *
		 * @return
		 * The actual damage to inflict.
		 */
		uint16_t onDetermineMoveDamage(const Pokemon &caster, const Pokemon &target, MoveID moveID, uint16_t initial, bool crit) const;

		/**
		 * Actions to take upon hitting a target.
		 *
		 * @param caster
		 * The casting pokemon.
		 *
		 * @param target
		 * The pokemon targeted by the move.
		 *
		 * @param moveID
		 * ID of the move used.
		 *
		 * @param dmg
		 * The inflicted damage.
		 *
		 * @param crit
		 * Whether the move hit critically.
		 */
		void onHit(Pokemon &caster, Pokemon &target, MoveID moveID, uint16_t dmg, bool crit) const;

		/**
		 * Actions to take upon missing a target.
		 *
		 * @param caster
		 * The casting pokemon.
		 *
		 * @param target
		 * The pokemon targeted by the move.
		 *
		 * @param moveID
		 * ID of the move used.
		 *
		 * @param dmg
		 * The damage that would've been inflicted.
		 */
		void onMiss(Pokemon &caster, Pokemon &target, MoveID moveID, uint16_t dmg) const;
	};
}



#endif // MOVEEFFECT_H_
