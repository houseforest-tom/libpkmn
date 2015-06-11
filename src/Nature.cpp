/*****************************************************************
 **' Nature.cpp
 *****************************************************************
 **' Created on: 20.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include <Nature.h>

namespace PKMN
{
	Nature::Nature(NatureID id, const Name &name, EPrimaryStat increase, EPrimaryStat decrease)
			: m_increasedStat(increase), m_decreasedStat(decrease)
	{
		assert(id > 0);				//Only accept IDs > 0
		assert(name.length() > 0);	//Reject empty name strings

		m_ID = id;
		m_name.assign(name);
	}

	/*****************************************************************
	 *****************************************************************/

	Nature PKMN::Nature::createNeutral(NatureID id, const Name &name)
	{
		return PKMN::Nature(id, name, (EPrimaryStat) 0, (EPrimaryStat) 0);
	}

	/*****************************************************************
	 *****************************************************************/

	StatValue PKMN::Nature::calcInfluencedStat(EPrimaryStat stat, StatValue initial) const
	{
		//Positive influence
		if (stat == m_increasedStat && stat != m_decreasedStat)
		{
			return (uint16_t) (initial * 1.1);
		}

		//Negative influence
		if (stat == m_decreasedStat && stat != m_increasedStat)
		{
			return (uint16_t) (initial * 0.9);
		}

		//No influence at all
		return initial;
	}
}
