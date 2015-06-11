/*****************************************************************
 **' PokemonAbility.h
 *****************************************************************
 **' Created on: 16.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef ABILITY_H_
#define ABILITY_H_

#include <Dependencies.h>
#include <IPrintable.h>
#include <functional>
#include <ScriptReferenceType.h>
#include <EMajorStatusAilment.h>
#include <EMinorStatusAilment.h>
#include <Move.h>

namespace PKMN
{
	/**
	 * Numerical id used for abilities.
	 */
	typedef uint16_t AbilityID;

	//ID aliases
	using AngelscriptContextID = unsigned;
	using AngelscriptModuleID  = unsigned;

	//Forward declarations
	class Species;
	class Pokemon;
	class ScriptInterface;

	class Ability : public IPrintable, public ScriptReferenceType
	{
	private:

		/**
		 * ID of the ability.
		 */
		AbilityID m_ID;

		/**
		 * Name of the ability.
		 */
		string m_name;

		/**
		 * Description text for the ability.
		 */
		string m_description;

		/**
		 * Script context ID.
		 */
		AngelscriptContextID m_scriptContextID;

		/**
		 * Script module ID.
		 */
		AngelscriptModuleID m_scriptModuleID;

		/**
		 * Script interface reference.
		 */
		ScriptInterface &m_scriptIF;

	public:

		/**
		 * Construct a new pokemon ability from the required information.
		 *
		 * @param id
		 * ID of the ability.
		 *
		 * @param name
		 * Name of the ability.
		 *
		 * @param desc
		 * Description text for the ability.
		 *
		 * @param scriptIF
		 * Reference to script interface.
		 */
		Ability(AbilityID id, const Name &name, const DescriptionText &desc, ScriptInterface &scriptIF);

		/**
		 * Print ability information to console.
		 */
		void print(void) const override;

		/**
		 * @return Ability ID.
		 */
		inline AbilityID getID(void) const
		{
			return m_ID;
		}

		/**
		 * @return Name of the ability.
		 */
		inline const Name &getName(void) const
		{
			return m_name;
		}

		/**
		 * @return Description text for the ability.
		 */
		inline const DescriptionText &getDescription(void) const
		{
			return m_description;
		}

		void onSwitchedIn(			Pokemon &self, Pokemon &other) const;
		void onSwitchedOut(			Pokemon &self, Pokemon &other) const;
		void onHitOpponent(			Pokemon &self, Pokemon &other, MoveID move, uint16_t dmg, bool crit) const;
		void onHitAlly(				Pokemon &self, Pokemon &other, MoveID move, uint16_t dmg, bool crit) const;
		void onHitByOpponent(		Pokemon &self, Pokemon &other, MoveID move, uint16_t dmg, bool crit) const;
		void onHitByAlly(			Pokemon &self, Pokemon &other, MoveID move, uint16_t dmg, bool crit) const;
		void onMajorStatusChanged(	Pokemon &self, Pokemon &other, EMajorStatusAilment status, bool suffers) const;
		void onMinorStatusChanged(	Pokemon &self, Pokemon &other, EMinorStatusAilment status, bool suffers) const;

		uint16_t onDetermineMoveDamage( const Pokemon &self, const Pokemon &other, MoveID moveID, uint16_t initial, bool crit) const;
	};
}

#endif // ABILITY_H_
