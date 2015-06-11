/*****************************************************************
 **' Type.h
 *****************************************************************
 **' Created on: 15.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef ETYPE_H_
#define ETYPE_H_

#include <Dependencies.h>

namespace PKMN
{
	/**
	 * Element types as used by pokemon species & moves.
	 */
	enum class EType : uint8_t
	{
		NORMAL,  	//!< NORMAL
		FIGHTING, 	//!< FIGHTING
		FLYING,  	//!< FLYING
		POISON,  	//!< POISON
		GROUND,  	//!< GROUND
		ROCK,    	//!< ROCK
		BUG,     	//!< BUG
		GHOST,   	//!< GHOST
		STEEL,   	//!< STEEL
		FIRE,    	//!< FIRE
		WATER,   	//!< WATER
		GRASS,   	//!< GRASS
		ELECTRIC, 	//!< ELECTRIC
		PSYCHIC, 	//!< PSYCHIC
		ICE,     	//!< ICE
		DRAGON,  	//!< DRAGON
		DARK,    	//!< DARK
		FAIRY,    	//!< FAIRY
		NONE		//!< NONE
	};

	namespace __EType__
	{
		/**
		 * Number of element types. This exludes the 'NONE' type.
		 */
		static const unsigned COUNT = 18;

		/**
		 * Convert a pokemon or move type to a readable string.
		 *
		 * @param type
		 * The type to convert.
		 *
		 * @return
		 * The readable string.
		 */
		static inline std::string tostring(EType type)
		{
			switch (type)
			{
				case EType::NORMAL:
					return "NORMAL";
				case EType::FIGHTING:
					return "FIGHTING";
				case EType::FLYING:
					return "FLYING";
				case EType::POISON:
					return "POISON";
				case EType::GROUND:
					return "GROUND";
				case EType::ROCK:
					return "ROCK";
				case EType::BUG:
					return "BUG";
				case EType::GHOST:
					return "GHOST";
				case EType::STEEL:
					return "STEEL";
				case EType::FIRE:
					return "FIRE";
				case EType::WATER:
					return "WATER";
				case EType::GRASS:
					return "GRASS";
				case EType::ELECTRIC:
					return "ELECTRIC";
				case EType::PSYCHIC:
					return "PSYCHIC";
				case EType::ICE:
					return "ICE";
				case EType::DRAGON:
					return "DRAGON";
				case EType::DARK:
					return "DARK";
				case EType::FAIRY:
					return "FAIRY";
				case EType::NONE:
					return "NONE";
			}

			return std::string();
		}
	}

	/**
	 * Lookup table containing all type effectiveness modifiers.
	 * To find out the effectiveness factor of a move of type M on a pokemon of type P,
	 * simply request the array member __TYPE_EFFECTIVENESS__[M][P].
	 * Using NONE as P is accepted as a valid request and will return 1.
	 * Using NONE as M however is invalid and will cause the application to crash.
	 * For convenience, use the getTypeEffectiveness(src, target) method.
	 */
	namespace //anonymous namespace
	{
		static const float __TYPE_EFFECTIVENESS__[ENUM_COUNT(EType)][ENUM_COUNT(EType) + 1] = {
				{ 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 }, //NORMAL Move
				{ 2.0, 1.0, 0.5, 0.5, 1.0, 2.0, 0.5, 0.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 2.0, 1.0, 2.0, 0.5, 1.0 }, //FIGTHING Move
				{ 1.0, 2.0, 1.0, 1.0, 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 }, //FLYING Move
				{ 1.0, 1.0, 1.0, 0.5, 0.5, 0.5, 1.0, 0.5, 0.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0 }, //POISON Move
				{ 1.0, 1.0, 0.0, 2.0, 1.0, 2.0, 0.5, 1.0, 2.0, 2.0, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 }, //GROUND Move
				{ 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 2.0, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0 }, //ROCK Move
				{ 1.0, 0.5, 0.5, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5, 0.5, 1.0, 2.0, 1.0, 2.0, 1.0, 1.0, 2.0, 0.5, 1.0 }, //BUG Move
				{ 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 1.0, 1.0 }, //GHOST Move
				{ 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5, 0.5, 1.0, 0.5, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0 }, //STEEL Move
				{ 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 2.0, 1.0, 2.0, 0.5, 0.5, 2.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0 }, //FIRE Move
				{ 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0 }, //WATER Move
				{ 1.0, 1.0, 0.5, 0.5, 2.0, 2.0, 1.0, 1.0, 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0 }, //GRASS Move
				{ 1.0, 1.0, 2.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0 }, //ELECTRIC Move
				{ 1.0, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 0.0, 1.0, 1.0 }, //PSYCHIC Move
				{ 1.0, 1.0, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 0.5, 0.5, 0.5, 2.0, 1.0, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0 }, //ICE Move
				{ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.0, 1.0 }, //DRAGON Move
				{ 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5, 1.0 }, //DARK Move
				{ 1.0, 2.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0 }, //FAIRY Move
				};
	}

	/**
	 * Returns the type effectiveness factor corresponding to a move of type src
	 * being casted on a pokemon of type target.
	 *
	 * @param src
	 * Type of the casted move, must not be EType::NONE.
	 *
	 * @param target
	 * Type of the defending pokemon.
	 * EType::NONE is valid input and will always cause a return value of 1.
	 *
	 * @return
	 * The effectiveness factor.
	 */
	static inline float getTypeEffectiveness(EType src, EType target)
	{
		return __TYPE_EFFECTIVENESS__[(unsigned) src][(unsigned) target];
	}
}

#endif // ETYPE_H_
