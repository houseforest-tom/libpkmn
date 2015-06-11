/*****************************************************************
 **' Evolution.h
 *****************************************************************
 **' Created on: 09.05.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef EVOLUTION_H_
#define EVOLUTION_H_

#include <EEvolutionCondition.h>

namespace PKMN
{
	/**
	 * Parameter used to check if evolution conditions are fulfilled.
	 */
	typedef uint16_t EvolutionParam;

	/**
	 * Numerical id used for species.
	 */
	typedef uint16_t SpeciesID;

	/**
	 * Describes one evolution path of a pokemon species.
	 */
	struct Evolution
	{
		/**
		 * The type of condition.
		 */
		EEvolutionCondition condition;

		/**
		 * The condition parameter.
		 */
		EvolutionParam param;

		/**
		 * The target species ID.
		 */
		SpeciesID species;
	};
}

#endif // EVOLUTION_H_
