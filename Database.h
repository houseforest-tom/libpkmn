/*****************************************************************
 **' Database.h
 *****************************************************************
 **' Created on: 20.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef DATABASE_H_
#define DATABASE_H_

#include <Dependencies.h>
#include <IPrintable.h>
#include <Species.h>
#include <Move.h>
#include <Ability.h>
#include <Nature.h>
#include <ScriptReferenceType.h>

namespace PKMN
{
	class Database : public IPrintable, public ScriptReferenceType
	{
	private:

		/**
		 * Vector containing all loaded natures.
		 */
		map<NatureID, Nature> m_natures;

		/**
		 * Vector containing all loaded abilities.
		 */
		map<AbilityID, Ability> m_abilities;

		/**
		 * Vector containing all loaded move effects.
		 */
		map<MoveEffectID, MoveEffect> m_moveEffects;

		/**
		 * Vector containing all loaded moves.
		 */
		map<MoveID, Move> m_moves;

		/**
		 * Vector containing all loaded species.
		 */
		map<SpeciesID, Species> m_species;

	public:
		/**
		 * Construct a new empty database.
		 */
		Database(void);

		/**
		 * Store a nature in the list for later use.
		 *
		 * @param nature
		 * The nature to store.
		 */
		void storeNature(const Nature &nature);

		/**
		 * Store an ability in the list for later use.
		 *
		 * @param ability
		 * The ability to store.
		 */
		void storeAbility(const Ability &ability);

		/**
		 * Store a move effect in the list for later use.
		 *
		 * @param effect
		 * The move effect to store.
		 */
		void storeMoveEffect(const MoveEffect &effect);

		/**
		 * Store a move in the list for later use.
		 *
		 * @param move
		 * The move to store.
		 */
		void storeMove(const Move &move);

		/**
		 * Store a species in the list for later use.
		 *
		 * @param species
		 * The species to store.
		 */
		void storeSpecies(const Species &species);

		/**
		 * Return a reference to the nature with the given ID.
		 *
		 * @param id
		 * ID of the nature to return.
		 *
		 * @return
		 * Reference to the nature.
		 */
		const Nature &getNature(NatureID id) const;

		/**
		 * @return
		 * Number of natures inside the database.
		 */
		unsigned getNatureCount(void) const;

		/**
		 * Return a reference to the ability with the given ID.
		 *
		 * @param id
		 * ID of the ability to return.
		 *
		 * @return
		 * Reference to the ability.
		 */
		const Ability &getAbility(AbilityID id) const;

		/**
		 * @return
		 * Number of abilites inside the database.
		 */
		unsigned getAbilityCount(void) const;

		/**
		 * Return a reference to the move effect with the given ID.
		 *
		 * @param id
		 * ID of the move effect to return.
		 *
		 * @return
		 * Reference to the move effect.
		 */
		const MoveEffect &getMoveEffect(MoveEffectID id) const;

		/**
		 * @return
		 * Number of move effects inside the database.
		 */
		unsigned getMoveEffectCount(void) const;

		/**
		 * Return a reference to the move with the given ID.
		 *
		 * @param id
		 * ID of the move to return.
		 *
		 * @return
		 * Reference to the move.
		 */
		const Move &getMove(MoveID id) const;

		/**
		 * @return
		 * Number of moves inside the database.
		 */
		unsigned getMoveCount(void) const;

		/**
		 * Return a reference to the species with the given ID.
		 *
		 * @param id
		 * ID of the species to return.
		 *
		 * @return
		 * Reference to the species.
		 */
		const Species &getSpecies(SpeciesID id) const;

		/**
		 * @return
		 * Number of species inside the database.
		 */
		unsigned getSpeciesCount(void) const;

		/**
		 * Load all species from the specified file.
		 *
		 * @param file
		 * The file to load the data from.
		 *
		 * Each species must have the following format inside the file:
		 * ID
		 * Name
		 * Type1
		 * Type2
		 * Abilities (,)
		 * Gender ratio
		 * Catch rate
		 * Weight
		 * Base XP yield
		 * Leveling rate
		 * EV Yields (,)
		 * Base friendship
		 * Description
		 * Base stats (,)
		 * Natural (levelup) moves (Level:Move,Move;Level:Move,Move,..)
		 * Compatible TMs (,)
		 * Compatible HMs (,)
		 * Egg group
		 * Egg moves (Species:Move,Move;Species:Move,Move,..)
		 * Evolutions (Condition,Param,Species,...)
		 *
		 * @return
		 * Result code.
		 * <ul>
		 * <li>-1 <=> IO / parser exception occured.</>
		 * <li>0 <=> No species data available.</>
		 * <li>Otherwise <=> Amount of species successfully loaded from file.</>
		 * </ul>
		 */
		int loadSpeciesFromFile(const Filename &file);

		/**
		 * Print database content information.
		 */
		void print(void) const;
	};
}

#endif // DATABASE_H_
