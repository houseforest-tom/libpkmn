/*****************************************************************
 **' LevelingRate.h
 *****************************************************************
 **' Created on: 15.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef ELEVELINGRATE_H_
#define ELEVELINGRATE_H_

#include <string>

namespace PKMN
{
	/**
	 * Possible pokemon species leveling rates.
	 */
	enum class ELevelingRate : uint8_t
	{
		ERRATIC,
		FAST,
		MEDIUM_FAST,
		MEDIUM_SLOW,
		SLOW,
		FLUCTUATING
	};

	namespace __ELevelingRate__
	{
		/**
		 * Number of leveling rates.
		 */
		static const unsigned COUNT = 6;

		/**
		 * Convert a leveling rate to a readable string.
		 *
		 * @param rate
		 * The leveling rate to stringify.
		 *
		 * @return
		 * The readable string.
		 */
		static inline std::string tostring(ELevelingRate rate)
		{
			switch (rate)
			{
				case ELevelingRate::ERRATIC:
					return "Erratic";
				case ELevelingRate::FAST:
					return "Fast";
				case ELevelingRate::MEDIUM_FAST:
					return "Medium Fast";
				case ELevelingRate::MEDIUM_SLOW:
					return "Medium Slow";
				case ELevelingRate::SLOW:
					return "Slow";
				case ELevelingRate::FLUCTUATING:
					return "Fluctuating";
			}

			return std::string();
		}
	}
}

#endif // ELEVELINGRATE_H_
