/*****************************************************************
 **' PokemonMove.h
 *****************************************************************
 **' Created on: 16.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef MOVE_H_
#define MOVE_H_

#include <Dependencies.h>
#include <EPrimaryStat.h>
#include <EType.h>
#include <EMoveContact.h>
#include <EMoveTarget.h>
#include <IPrintable.h>
#include <ScriptReferenceType.h>
#include <MoveEffect.h>

namespace PKMN
{
	/**
	 * Numerical id used for moves.
	 */
	typedef uint16_t MoveID;

	/**
	 * Move base power value [0..255].
	 */
	typedef uint8_t MoveBasePower;

	/**
	 * Move PP.
	 * If no PP are left, the move cannot be moved.
	 */
	typedef uint8_t MovePP;

	/**
	 * Move priority.
	 * Higher priority moves will generally hit before lower priority ones.
	 * <ul>
	 * <li>0 <=> default priority.</>
	 * <li><0 <=> lower priority.</>
	 * <li>>0 <=> higher priority.</>
	 * </ul>
	 */
	typedef int8_t MovePriority;

	/**
	 * Move effect ID.
	 */
	typedef uint16_t MoveEffectID;

	/**
	 * Additional move flags.
	 */
	typedef uint8_t MoveFlag;
	typedef vector<MoveFlag> MoveFlagList;

	/**
	 * Number of moves a pokemon may know simultaneously.
	 */
	static const unsigned MOVESET_SIZE = 4;

	/**
	 * Represents a pokemon's moveset.
	 */
	class Moveset : public ScriptReferenceType
	{
	private:
		/**
		 * IDs of the moves contained within this moveset.
		 */
		MoveID m_moveIDs[MOVESET_SIZE] = { 0 };

	public:
		/**
		 * Get a move ID contained within this moveset.
		 *
		 * @param slot
		 * The move  slot.
		 *
		 * @return The move ID.
		 */
		inline MoveID getMoveID(uint8_t slot) const
		{
			assert(slot < MOVESET_SIZE);
			return m_moveIDs[slot];
		}

		MoveID operator[](uint8_t slot) const
		{
			return getMoveID(slot);
		}

		MoveID &operator[](uint8_t slot)
		{
			return m_moveIDs[slot];
		}
	};

	/**
	 * Represents a move that a pokemon can learn and use in battle.
	 */
	class Move : public IPrintable, public ScriptReferenceType
	{
	private:

		/**
		 * ID of the move.
		 */
		MoveID m_ID;

		/**
		 * Name of the move.
		 */
		Name m_name;

		/**
		 * Description text for the move.
		 */
		DescriptionText m_description;

		/**
		 * Type of the move.
		 */
		EType m_type;

		/**
		 * Move contact.
		 */
		EMoveContact m_contact;

		/**
		 * Move default maximum PP.
		 */
		MovePP m_pp;

		/**
		 * Move base power.
		 */
		MoveBasePower m_basePower;

		/**
		 * Move accuracy [0..100] where 0 <=> always hits, otherwise --% chance.
		 */
		Percentage m_accuracy;

		/**
		 * Move priority [-6..6] where 0 <=> default.
		 */
		MovePriority m_priority;

		/**
		 * Move effect ID.
		 */
		MoveEffectID m_effectID;

		/**
		 * Move effect chance in percent [0..100].
		 */
		Percentage m_effectChance;

		/**
		 * Move target.
		 */
		EMoveTarget m_target;

		/**
		 * Move flags.
		 */
		MoveFlagList m_flags;

	public:

		/**
		 * Constructs a new pokemon move from all required information.
		 *
		 * @param id
		 * Move ID.
		 * @param name
		 * Move name.
		 * @param type
		 * Move type.
		 * @param contact
		 * Move class describing contact made w/ opponent.
		 * @param pp
		 * Default maximum PP.
		 * @param pwr
		 * Move base power.
		 * @param acc
		 * Accuracy [0..100] where 0 <=> always hits, otherwise --% chance.
		 * @param prio
		 * Move pritoriy [-6..6] where 0 <=> default.
		 * @param effect
		 * Move effect code.
		 * @param effectChance
		 * Move effect trigger chance in percent.
		 * @param target
		 * Move target.
		 * @param flags
		 * Move flags.
		 * @param desc
		 * Description text.
		 */
		Move(MoveID id, const Name &name, EType type, EMoveContact contact, MovePP pp,
				MoveBasePower pwr, Percentage acc, MovePriority prio, MoveEffectID effect,
				Percentage effectChance, EMoveTarget target, const MoveFlagList &flags,
				const DescriptionText &desc);

		/**
		 * Print move information to console.
		 */
		void print(void) const override;

		/**
		 * @return Move ID.
		 */
		inline MoveID getID(void) const
		{
			return m_ID;
		}

		/**
		 * @return Move name.
		 */
		inline const Name &getName(void) const
		{
			return m_name;
		}

		/**
		 * @return Move type.
		 */
		inline EType getType(void) const
		{
			return m_type;
		}

		/**
		 * @return Move class describing contact made w/ foe.
		 */
		inline EMoveContact getContact(void) const
		{
			return m_contact;
		}

		/**
		 * @return Move base power.
		 */
		inline MoveBasePower getBasePower(void) const
		{
			return m_basePower;
		}

		/**
		 * @return Default move max PP.
		 */
		inline MovePP getPP(void) const
		{
			return m_pp;
		}

		/**
		 * @return Move accuracy [0..100] where 0 <=> always hits, else --% chance.
		 */
		inline Percentage getAccuracy(void) const
		{
			return m_accuracy;
		}

		/**
		 * @return Move priority [-6..6] where 0 <=> default.
		 */
		inline MovePriority getPriority(void) const
		{
			return m_priority;
		}

		/**
		 * @return Move description text.
		 */
		inline const DescriptionText &getDescription(void) const
		{
			return m_description;
		}

		/**
		 * @return Move effect ID.
		 */
		inline MoveEffectID getEffectID(void) const
		{
			return m_effectID;
		}

		/**
		 * @return Move effect chance in percent [0..100].
		 */
		inline Percentage getEffectChance(void) const
		{
			return m_effectChance;
		}

		/**
		 * @return The flags set for this move.
		 */
		inline const MoveFlagList &getFlags(void) const
		{
			return m_flags;
		}

		/**
		 * @return Whether the specified flag is set for this move.
		 */
		inline bool checkFlag(MoveFlag flag) const
		{
			return invector(m_flags, flag);
		}
	};
}
#endif // MOVE_H_
