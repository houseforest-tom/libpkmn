/*****************************************************************
 **' EBattleType.h
 *****************************************************************
 **' Created on: 28.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef EBATTLETYPE_H_
#define EBATTLETYPE_H_

namespace PKMN
{
	/**
	 * Possible battle types.
	 */
	enum class EBattleType : uint8_t
	{
		SINGLE_WILD,   //!< Single battle against a wild pokemon
		SINGLE_TRAINER,//!< Single battle against a trainer
		DOUBLE_WILD,   //!< Double battle against a wild pokemon
		DOUBLE_TRAINER //!< Double battle against a trainer
	};
}

#endif // EBATTLETYPE_H_
