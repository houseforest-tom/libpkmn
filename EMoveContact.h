/*****************************************************************
 **' EMoveContact.h
 *****************************************************************
 **' Created on: 20.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef EMOVECONTACT_H_
#define EMOVECONTACT_H_

#include <string>

namespace PKMN
{
	/**
	 * Pokemon move classes describing contact made with opponent.
	 */
	enum class EMoveContact : uint8_t
	{
		STATUS,  	//!< STATUS
		PHYSICAL,   //!< PHYSICAL
		SPECIAL  	//!< SPECIAL
	};

	namespace __EMoveContact__
	{
		/**
		 * Numver of move contact specifications.
		 */
		static const unsigned COUNT = 3;

		/**
		 * Convert a move contact id to a readable string.
		 *
		 * @param contact
		 * The move contact to convert.
		 *
		 * @return
		 * The readable string.
		 */
		static inline std::string tostring(EMoveContact contact)
		{
			switch (contact)
			{
				case EMoveContact::STATUS:   return "STATUS";
				case EMoveContact::PHYSICAL: return "PHYSICAL";
				case EMoveContact::SPECIAL:  return "SPECIAL";
			}

			return std::string();
		}
	}
}

#endif // EMOVECONTACT_H_
