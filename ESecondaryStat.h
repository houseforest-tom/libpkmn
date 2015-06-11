/*****************************************************************
 **' ESecondaryStat.h
 *****************************************************************
 **' Created on: 21.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef ESECONDARYSTAT_H_
#define ESECONDARYSTAT_H_

#include <string>

namespace PKMN
{
	/**
	 * Pokemon secondary stats.
	 */
	enum class ESecondaryStat : uint8_t
	{
		ACCURACY, //!< ACCURACY
		EVASION,  //!< EVASION
		CRITICAL  //!< CRITICAL
	};

	namespace __ESecondaryStat__
	{
		/**
		 * Number of secondary stats.
		 */
		static const unsigned COUNT = 2;

		/**
		 * Convert a secondary stat to a readable string.
		 *
		 * @param stat
		 * The stat to convert.
		 *
		 * @return
		 * The readable string.
		 */
		static inline std::string tostring(ESecondaryStat stat)
		{
			switch (stat)
			{
				case ESecondaryStat::ACCURACY:
					return "ACCURACY";
				case ESecondaryStat::EVASION:
					return "EVASION";
				case ESecondaryStat::CRITICAL:
					return "CRITICAL";
			}

			return std::string();
		}
	}
}

#endif // ESECONDARYSTAT_H_
