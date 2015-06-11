/*****************************************************************
 **' Nature.h
 *****************************************************************
 **' Created on: 20.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef NATURE_H_
#define NATURE_H_

#include <Dependencies.h>
#include <EPrimaryStat.h>
#include <ScriptReferenceType.h>

namespace PKMN
{
	/**
	 * ID of a nature.
	 */
	typedef uint16_t NatureID;

	/**
	 * Represents a pokemon nature.
	 */
	class Nature : public ScriptReferenceType
	{
	private:
		/**
		 * ID of the nature.
		 */
		NatureID m_ID;

		/**
		 * Name of the nature.
		 */
		Name m_name;

		/**
		 * Increased stat.
		 */
		EPrimaryStat m_increasedStat;

		/**
		 * Decreased stat.
		 */
		EPrimaryStat m_decreasedStat;

	public:
		/**
		 * Construct a new pokemon nature from the required information.
		 * If increase and decreased stat are the same, this nature is neutral.
		 *
		 * @param id
		 * Nature id.
		 * @param name
		 * Nature name.
		 * @param increase
		 * The stat that's increased by this nature.
		 * @param decrease
		 * The stat that's decreased by this nature.
		 */
		Nature(NatureID id, const Name &name, EPrimaryStat increase, EPrimaryStat decrease);

		/**
		 * Creates and returns a neutral nature.
		 * Shortcut to calling the construct with increased stat equal to decreased.
		 *
		 * @param id
		 * Nature id.
		 * @param name
		 * Nature name.
		 *
		 * @return
		 * The constructed neutral Nature.
		 */
		static Nature createNeutral(NatureID id, const Name &name);

		/**
		 * @return Nature ID.
		 */
		inline NatureID getID(void) const
		{
			return m_ID;
		}

		/**
		 * @return Nature name.
		 */
		inline const Name &getName(void) const
		{
			return m_name;
		}

		/**
		 * @return The stat increased by this nature.
		 */
		inline EPrimaryStat getIncreasedStat(void) const
		{
			return m_increasedStat;
		}

		/**
		 * @return The stat decreased by this nature.
		 */
		inline EPrimaryStat getDecreasedStat(void) const
		{
			return m_decreasedStat;
		}

		/**
		 * @return Whether this nature is neutral.
		 */
		inline bool isNeutral(void) const
		{
			return m_increasedStat == m_decreasedStat;
		}

		/**
		 * Calculate and return the value of a stat after being modified by this nature.
		 *
		 * @param stat
		 * The stat to calculate the modified value of.
		 * @param initial
		 * The initial value of the stat.
		 *
		 * @return
		 * The modified value.
		 */
		StatValue calcInfluencedStat(EPrimaryStat stat, StatValue initial) const;
	};
}

#endif // NATURE_H_
