/*****************************************************************
 **' EMinorStatusAilment.h
 *****************************************************************
 **' Created on: 24.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef EMINORSTATUSAILMENT_H_
#define EMINORSTATUSAILMENT_H_

#include <string>

namespace PKMN
{
	/**
	 * Enumeration of minor status ailments a pokemon may suffer from.
	 */
	enum class EMinorStatusAilment : uint8_t
	{
		CONFUSION,	 //!< CONFUSION
		FLINCH,		 //!< FLINCH
		SEED,		 //!< SEED
		INFATUATION, //!< INFATUATION
		CURSE,		 //!< CURSE
		NIGHTMARE	 //!< NIGHTMARE
	};

	namespace __EMinorStatusAilment__
	{
		/**
		 * Number of minor status ailments.
		 */
		static const unsigned COUNT = 6;

		/**
		 * Convert a minor status ailment to a readable string.
		 *
		 * @param ailment
		 * The minor status ailment.
		 *
		 * @return The readable string.
		 */
		static inline std::string tostring(EMinorStatusAilment ailment)
		{
			switch(ailment)
			{
				case EMinorStatusAilment::CONFUSION: 	return "CONFUSION";
				case EMinorStatusAilment::FLINCH: 		return "FLINCH";
				case EMinorStatusAilment::SEED: 		return "SEED";
				case EMinorStatusAilment::INFATUATION: 	return "INFATUATION";
				case EMinorStatusAilment::CURSE: 		return "CURSE";
				case EMinorStatusAilment::NIGHTMARE: 	return "NIGHTMARE";
			}

			return std::string();
		}
	}
}

#endif // EMINORSTATUSAILMENT_H_
