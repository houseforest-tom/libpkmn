/*****************************************************************
 **' EMoveTarget.h
 *****************************************************************
 **' Created on: 25.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef EMOVETARGET_H_
#define EMOVETARGET_H_

namespace PKMN
{
	/**
	 * All types of targets a move can hit.
	 */
	enum class EMoveTarget : uint8_t
	{
		SINGLE_BESIDES_USER,      //!< SINGLE_BESIDES_USER
		NONE,                     //!< NONE
		RANDOM_OPPONENT,          //!< RANDOM_OPPONENT
		ALL_OPPONENTS,            //!< ALL_OPPONENTS
		ALL_BESIDES_USER,         //!< ALL_BESIDES_USER
		USER,                     //!< USER
		BOTH_TEAMS,               //!< BOTH_TEAMS
		USER_TEAM,                //!< USER_TEAM
		OPPONENT_TEAM,            //!< OPPONENT_TEAM
		USER_PARTNER,             //!< USER_PARTNER
		USER_OR_USER_PARTNER,     //!< USER_OR_USER_PARTNER
		SINGLE_OPPONENT,          //!< SINGLE_OPPONENT
		DIRECTLY_OPPOSITE_OPPONENT//!< DIRECTLY_OPPOSITE_OPPONENT
	};

	namespace __EMoveTarget__
	{
		/**
		 * Number of move target enumeration values.
		 */
		static const unsigned COUNT = 13;

		/**
		 * Stringify a move target value.
		 *
		 * @param target
		 * The move target value to stringify.
		 *
		 * @return The resulting string.
		 */
		static inline std::string tostring(EMoveTarget target)
		{
			switch(target)
			{
				case EMoveTarget::SINGLE_BESIDES_USER: 			return "Single besides user";
				case EMoveTarget::NONE: 						return "None";
				case EMoveTarget::RANDOM_OPPONENT: 				return "Random opponent";
				case EMoveTarget::ALL_OPPONENTS: 				return "All opponents";
				case EMoveTarget::ALL_BESIDES_USER: 			return "All besides user";
				case EMoveTarget::USER: 						return "User";
				case EMoveTarget::BOTH_TEAMS: 					return "Both teams";
				case EMoveTarget::USER_TEAM: 					return "User team";
				case EMoveTarget::OPPONENT_TEAM: 				return "Opponent team";
				case EMoveTarget::USER_PARTNER: 				return "User partner";
				case EMoveTarget::USER_OR_USER_PARTNER: 		return "User or user partner";
				case EMoveTarget::SINGLE_OPPONENT: 				return "Single opponent";
				case EMoveTarget::DIRECTLY_OPPOSITE_OPPONENT: 	return "Directly opposite opponent";
			}

			return std::string();
		}
	}
}



#endif // EMOVETARGET_H_
