/*****************************************************************
 **' EEvolutionCondition.h
 *****************************************************************
 **' Created on: 09.05.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef EEVOLUTIONCONDITION_H_
#define EEVOLUTIONCONDITION_H_

namespace PKMN
{
	/**
	 * Enumeration of possible evolution conditions.
	 */
	enum class EEvolutionCondition : uint8_t
	{
		//Parameter: -
		//-----------------------------------------

		//Happiness >= 220.
		HAPPINESS,

		//Same as HAPPINESS, only during daytime.
		HAPPINESS_DAY,

		//Same as HAPPINESS, only during nighttime.
		HAPPINESS_NIGHT,

		//Evolves by trading
		TRADE,


		//Parameter: Level
		//----------------------------------------

		//Reach designated level.
		LEVEL,

		//Same as LEVEL, pokemon must be male.
		LEVEL_MALE,

		//Same as LEVEL, pokemon must be female.
		LEVEL_FEMALE,

		//Same as LEVEL, ATK stat must be higher than DEF.
		LEVEL_ATK_OVER_DEF,

		//Same as LEVEL, DEF stat must be higher than ATK.
		LEVEL_DEF_OVER_ATK,

		//Same as LEVEL, ATK stat must be equal to DEF.
		LEVEL_ATK_EQUALS_DEF,

		//Same as LEVEL, Trainer ID must end with 0,..,4.
		LEVEL_TRAINER_ID_LO,

		//Same as LEVEL, Trainer ID must end with 5,..,9.
		LEVEL_TRAINER_ID_HI,


		//Parameter: Item ID
		//----------------------------------------

		//Item used on pokemon.
		ITEM,

		//Same as ITEM, pokemon must be male.
		ITEM_MALE,

		//Same as ITEM, pokemon must be female.
		ITEM_FEMALE,

		//Levelup while holding an item.
		ITEM_HOLD,

		//Same as ITEM_HOLD, only during daytime
		ITEM_HOLD_DAY,

		//Same as ITEM_HOLD, only during nighttime.
		ITEM_HOLD_NIGHT,

		//Same as ITEM, but instead of leveling up, the pokemon must be traded.
		ITEM_HOLD_TRADE,


		//Parameter: Species ID
		//----------------------------------------

		//Levelup while species in team.
		SPECIES_IN_TEAM,

		//Same as TRADE, must be traded against a given species.
		TRADE_SPECIES,


		//Parameter: Map ID
		//----------------------------------------

		//Levelup at the designated location.
		LOCATION
	};
}

#endif // EEVOLUTIONCONDITION_H_
