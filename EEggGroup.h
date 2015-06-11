/*****************************************************************
 **' EEggGroup.h
 *****************************************************************
 **' Created on: 08.05.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef EEGGGROUP_H_
#define EEGGGROUP_H_

namespace PKMN
{
	/**
	 * Enumeration of pokemon egg groups.
	 * The egg group influences which partners a species can breed with.
	 */
	enum class EEggGroup : uint8_t
	{
		MONSTER,      //!< MONSTER
		HUMAN_LIKE,   //!< HUMAN_LIKE
		WATER1,       //!< WATER1
		WATER2,       //!< WATER2
		WATER3,       //!< WATER3
		BUG,          //!< BUG
		FLYING,       //!< FLYING
		FIELD,        //!< FIELD
		FAIRY,        //!< FAIRY
		GRASS,        //!< GRASS
		MINERAL,      //!< MINERAL
		AMORPHOUS,    //!< AMORPHOUS
		DITTO,        //!< DITTO
		DRAGON,       //!< DRAGON
		UNDISCOVERED, //!< UNDISCOVERED
		GENDER_UNKNOWN//!< GENDER_UNKNOWN
	};

	namespace __EEggGroup__
	{
		/**
		 * Number of different egg groups.
		 */
		static const unsigned COUNT = 8;

		/**
		 * Convert an egg group to a readable string.
		 *
		 * @param eggGroup
		 * The egg group to convert.
		 *
		 * @return
		 * The stringifed object.
		 */
		static inline std::string tostring(EEggGroup eggGroup)
		{
			switch (eggGroup)
			{
				case EEggGroup::MONSTER: 		return "Monster";
				case EEggGroup::HUMAN_LIKE: 	return "Human-like";
				case EEggGroup::WATER1: 		return "Water 1";
				case EEggGroup::WATER2: 		return "Water 2";
				case EEggGroup::WATER3: 		return "Water 3";
				case EEggGroup::BUG: 			return "Bug";
				case EEggGroup::FLYING: 		return "Flying";
				case EEggGroup::FIELD: 			return "Field";
				case EEggGroup::FAIRY: 			return "Fairy";
				case EEggGroup::GRASS: 			return "Grass";
				case EEggGroup::MINERAL: 		return "Mineral";
				case EEggGroup::AMORPHOUS: 		return "Amorphous";
				case EEggGroup::DITTO: 			return "Ditto";
				case EEggGroup::DRAGON:			return "Dragon";
				case EEggGroup::UNDISCOVERED:	return "Undiscovered";
				case EEggGroup::GENDER_UNKNOWN:	return "Gender unknown";
			}

			return std::string();
		}
	}
}

#endif // EEGGGROUP_H_
