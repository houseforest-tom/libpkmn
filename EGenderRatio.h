/*****************************************************************
 **' GenderRatio.h
 *****************************************************************
 **' Created on: 15.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef EGENDERRATIO_H_
#define EGENDERRATIO_H_

#include <string>

namespace PKMN
{
	/**
	 * Describes the possible ratios of female to male encounters.
	 * Genderless species should also have a genderless gender ratio set.
	 */
	enum class EGenderRatio : uint8_t
	{

		M_ONLY,		//Male only
		M_7_OVER_8,	//7 out of 8 male
		M_3_OVER_4,	//3 out of 4 male
		EQUAL,		//Equal parts
		F_3_OVER_4,	//3 out of 4 female
		F_7_OVER_8,	//7 out of 8 female
		F_ONLY,		//Female only
		GENDERLESS	//No gender specified
	};

	namespace __EGenderRatio__
	{
		/**
		 * Number of possible gender ratios.
		 */
		static const unsigned COUNT = 8;

		/**
		 * Convert a gender ratio to a readable string.
		 *
		 * @param genderRatio
		 * The gender ratio to convert.
		 *
		 * @return
		 * The stringifed object.
		 */
		static inline std::string tostring(EGenderRatio genderRatio)
		{
			switch (genderRatio)
			{
				case EGenderRatio::M_ONLY:
					return "Male Only";
				case EGenderRatio::M_7_OVER_8:
					return "Male 7/8";
				case EGenderRatio::M_3_OVER_4:
					return "Male 3/4";
				case EGenderRatio::EQUAL:
					return "Equal";
				case EGenderRatio::F_3_OVER_4:
					return "Female 3/4";
				case EGenderRatio::F_7_OVER_8:
					return "Female 7/8";
				case EGenderRatio::F_ONLY:
					return "Female Only";
				case EGenderRatio::GENDERLESS:
					return "Genderless";
			}

			return std::string();
		}
	}
}

#endif // EGENDERRATIO_H_
