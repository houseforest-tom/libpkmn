/*****************************************************************
 **' PokemonTeam.h
 *****************************************************************
 **' Created on: 23.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef PARTY_H_
#define PARTY_H_

#include <Pokemon.h>
#include <ScriptReferenceType.h>

namespace PKMN
{
	/**
	 * Maximum number of members inside a pokemon team.
	 */
	static const unsigned MAX_TEAM_SIZE = 6;

	/**
	 * Holds a collection of pokemon.
	 */
	class Party : public IPrintable, public ScriptReferenceType
	{
	private:
		/**
		 * The member pokemon of this team.
		 * May have a maximum size of MAX_TEAM_SIZE.
		 */
		vector<Pokemon> m_members;

	public:
		/**
		 * Construct a new empty pokemon party.
		 */
		Party(void);

		/**
		 * Construct a new pokemon party containing the specified members.
		 *
		 * @param members
		 * List of pokemon to include in the team.
		 */
		Party(const vector<Pokemon> &members);

		/**
		 * @return Size of the pokemon team.
		 */
		inline unsigned getSize(void) const
		{
			return m_members.size();
		}

		/**
		 * Return a const reference to the team member at the given slot.
		 *
		 * @param slot
		 * Which slot.
		 *
		 * @return
		 * Const reference to member in slot.
		 */
		inline const Pokemon &operator[](unsigned slot) const
		{
			assert(slot < getSize());
			return m_members[slot];
		}

		//Wrapper function for script exposure.
		inline const Pokemon &scriptGetMemberReadonly(unsigned slot){ return (*this)[slot]; }

		/**
		 * Return a mutable reference to the team member at the given slot.
		 *
		 * @param slot
		 * Which slot.
		 *
		 * @return
		 * Mutable reference to member in slot.
		 */
		inline Pokemon &operator[](unsigned slot)
		{
			assert(slot < getSize());
			return m_members[slot];
		}

		//Wrapper function for script exposure.
		inline Pokemon &scriptGetMemberMutable(unsigned slot){ return (*this)[slot]; }

		/**
		 * Overwrite an existing member with a new one.
		 * Do not use to append members at the end,
		 * use addMember(const Pokemon&) instead.
		 *
		 * @param slot
		 * Which slot. Must be in use currently.
		 *
		 * @param member
		 * The new member.
		 *
		 * @return
		 * True on success, false on failure.
		 */
		bool overwriteMember(unsigned slot, const Pokemon &member);

		/**
		 * Appends a new member at the back of the team.
		 *
		 * @param member
		 * The new member.
		 *
		 * @return
		 * True on success, false on failure.
		 */
		bool addMember(const Pokemon &member);

		/**
		 * Removes the member at the given slot.
		 * This decreases the team size by one and moves all
		 * remaining pokemon behind the slot one slot up front.
		 *
		 * @param slot
		 * The slot to remove the member in.
		 *
		 * @return
		 * True on success, false on failure.
		 */
		bool removeMember(unsigned slot);

		/**
		 * Removes all members from this team.
		 */
		void clear(void);

		/**
		 * Print team members.
		 */
		void print(void) const;
	};
}

#endif // PARTY_H_
