/*****************************************************************
 **' EMajorStatusAilment.h
 *****************************************************************
 **' Created on: 22.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef EMAJORSTATUSAILMENT_H_
#define EMAJORSTATUSAILMENT_H_

#include <string>

namespace PKMN
{
	/**
	 * Enumeration of major status ailments a pokemon may have.
	 */
	enum class EMajorStatusAilment : uint8_t
	{
		NONE,		//!< NONE
		SLEEP,      //!< SLEEP
		POISON,    	//!< POISOND
		PARALYSIS,  //!< PARALYSIS
		BURN,      	//!< BURN
		FREEZE,     //!< FREEZE
		TOXIC,   	//!< TOXIC
		FAINTED		//!< FAINTED
	};

	namespace __EMajorStatusAilment__
	{
		/**
		 * Number of major status ailments.
		 */
		static const unsigned COUNT = 8;

		/**
		 * Convert a major status ailment to a readable string.
		 *
		 * @param ailment
		 * The major status ailment.
		 *
		 * @return
		 * The readable string.
		 */
		static inline std::string tostring(EMajorStatusAilment ailment)
		{
			switch (ailment)
			{
				case EMajorStatusAilment::NONE: 		return "None (OK)";
				case EMajorStatusAilment::SLEEP: 		return "Sleep (SLP)";
				case EMajorStatusAilment::POISON: 		return "Poisoning (PSN)";
				case EMajorStatusAilment::PARALYSIS: 	return "Paralysis (PAR)";
				case EMajorStatusAilment::BURN: 		return "Burn (BRN)";
				case EMajorStatusAilment::FREEZE: 		return "Freeze (FRZ)";
				case EMajorStatusAilment::TOXIC: 		return "Badly poisoned (TOX)";
				case EMajorStatusAilment::FAINTED:		return "Fainted (FNT)";
			}

			return std::string();
		}
	}
}

#endif // EMAJORSTATUSAILMENT_H_
