/*****************************************************************
 **' BaseStats.h
 *****************************************************************
 **' Created on: 15.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef EPRIMARYSTAT_H_
#define EPRIMARYSTAT_H_

#include <string>

namespace PKMN
{
	/**
	 * Pokemon primary stats.
	 */
	enum class EPrimaryStat : uint8_t
	{
		HP,		//HP
		ATK,	//Attack
		DEF,	//Defense
		SPATK,	//Special Attack
		SPDEF,	//Special Defense
		SPEED	//Speed
	};

	namespace __EPrimaryStat__
	{
		/**
		 * Number of pokemon primary stats.
		 */
		static const unsigned COUNT = 6;

		/**
		 * Convert a primary stat to a readable string.
		 *
		 * @param stat
		 * The stat to convert.
		 *
		 * @return
		 * The readable string.
		 */
		static inline std::string tostring(EPrimaryStat stat)
		{
			switch (stat)
			{
				case EPrimaryStat::HP:
					return "HP";
				case EPrimaryStat::ATK:
					return "ATK";
				case EPrimaryStat::DEF:
					return "DEF";
				case EPrimaryStat::SPATK:
					return "SPATK";
				case EPrimaryStat::SPDEF:
					return "SPDEF";
				case EPrimaryStat::SPEED:
					return "SPEED";
			}

			return std::string();
		}
	}
}

#endif // EPRIMARYSTAT_H_
