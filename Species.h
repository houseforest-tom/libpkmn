/*****************************************************************
 **' PokemonSpecies.h
 *****************************************************************
 **' Created on: 15.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef SPECIES_H_
#define SPECIES_H_

#include <EGenderRatio.h>
#include <ELevelingRate.h>
#include <EPrimaryStat.h>
#include <EType.h>
#include <EEggGroup.h>
#include <IPrintable.h>
#include <Ability.h>
#include <Move.h>
#include <Evolution.h>
#include <ScriptReferenceType.h>

namespace PKMN
{
	/**
	 * Species catch rate.
	 * [0-255] where 255 is easiest to capture.
	 */
	typedef uint8_t CatchRate;

	/**
	 * Friendship value.
	 * [0-255] where 255 means highest possible affection.
	 */
	typedef uint8_t FriendshipValue;

	/**
	 * Technical machine (TM) ID.
	 */
	typedef uint16_t TechnicalMachineID;

	/**
	 * Hidden machine (HM) ID.
	 */
	typedef uint16_t HiddenMachineID;

	/**
	 * Describes a species of pokemon.
	 * Contains all information about base stats, moves to learn,
	 * possible evolutions etc.
	 */
	class Species : public IPrintable, public ScriptReferenceType
	{
	private:

		/**
		 * Species ID.
		 */
		SpeciesID m_ID;

		/**
		 * Name of the species.
		 */
		Name m_name;

		/**
		 * Primary and secondary type of the species.
		 */
		EType m_types[2];

		/**
		 * Indices of abilities, this species can have.
		 */
		vector<AbilityID> m_possibleAbilities;

		/**
		 * Species appearance gender ratio.
		 */
		EGenderRatio m_genderRatio;

		/**
		 * Species catch rate.
		 * [0-255] where 255 is easiest to capture.
		 */
		CatchRate m_catchRate;

		/**
		 * Weight of the pokemon species in kg.
		 */
		float m_weight;

		/**
		 * Base experience points yielded by defeating this species.
		 */
		Experience m_baseExpYield;

		/**
		 * Species leveling rate.
		 */
		ELevelingRate m_levelingRate;

		/**
		 * Effort value points yielded by this species.
		 */
		EffortValue m_evYields[ENUM_COUNT(EPrimaryStat)];

		/**
		 * Base friendship value of this species.
		 */
		FriendshipValue m_baseFriendship;

		/**
		 * Description text to appear in the pokedex.
		 */
		DescriptionText m_description;

		/**
		 * This species' base stats.
		 */
		BaseStatValue m_baseStats[ENUM_COUNT(EPrimaryStat)];

		/**
		 * Moves that this species can learn by leveling up.
		 * Stored as tuples of <level, vector of move ids to learn>
		 */
		map<Level, vector<MoveID>> m_naturalMoves;

		/**
		 * Indices of TMs that this species may learn.
		 */
		vector<TechnicalMachineID> m_compatibleTMs;

		/**
		 * Indices of HMs that this species may learn.
		 */
		vector<HiddenMachineID> m_compatibleHMs;

		/**
		 * This species' egg groups.
		 */
		vector<EEggGroup> m_eggGroups;

		/**
		 * Egg-moves that this species can learn.
		 * Stored as tuples of <partner species id, vector of learnable move ids>
		 */
		map<SpeciesID, vector<MoveID>> m_eggMoves;

		/**
		 * List of possible evolutions.
		 */
		vector<Evolution> m_evolutions;

	public:
		/**
		 * Constructs a new pokemon species from all required information.
		 *
		 * @param id
		 * Species ID.
		 * @param name
		 * Species name.
		 * @param types
		 * Vector containing 1 or two type identifiers, indication primary & secondary types.
		 * @param abilities
		 * Vector containing indices of all possible species abilities.
		 * @param genderRatio
		 * Gender ratio.
		 * @param catchRate
		 * Catch rate [0..255] where 255 <=> easiest to catch.
		 * @param weight
		 * Weight in kg.
		 * @param baseExpYield
		 * Base experience point yield when defeated in battle.
		 * @param lvlRate
		 * Level rate.
		 * @param evYields
		 * Vector of numbers determining the yielded EV points for each corresponding base stat.
		 * Must have as many elements as base stats exist.
		 * @param baseFriendship
		 * Base friendship value [0..255] where 255 <=> maximum friendship.
		 * @param desc
		 * Pokedex description text.
		 * @param base
		 * Vector containing all base stat values [0..255].
		 * Must have as many elements as base stats exist.
		 * @param naturalMoves
		 * Tuples of <level, vector of move ids to learn> that describe when this species learns which moves.
		 * @param compatTM
		 * Vector of indices of compatible TMs.
		 * @param compatHM
		 * Vector of indices of compatible HMs.
		 * @param eggGroups
		 * Egg groups.
		 * @param eggMoves
		 * Tuples of <partner species id, vector of learnable move ids> that describe this species' egg moveset.
		 * @param evolutions
		 * List of possible evolutions.
		 */
		Species(SpeciesID id, const Name &name, const vector<EType> &types, const vector<AbilityID> &abilities,
				EGenderRatio genderRatio, CatchRate catchRate, float weight, Experience baseExpYield, ELevelingRate lvlRate,
				const vector<EffortValue> &evYields, FriendshipValue baseFriendship, const DescriptionText &desc,
				const vector<BaseStatValue> &base, const map<Level, vector<MoveID>> &naturalMoves,
				const vector<TechnicalMachineID> &compatTM, const vector<HiddenMachineID> &compatHM,
				const vector<EEggGroup> &eggGroups, const map<SpeciesID, vector<MoveID>> &eggMoves,
				const vector<Evolution> &evolutions);

		/**
		 * Print species information to console.
		 */
		void print(void) const override;

		/**
		 * @return Species ID.
		 */
		inline SpeciesID getID(void) const
		{
			return m_ID;
		}

		/**
		 * @return Species Name.
		 */
		inline const Name &getName(void) const
		{
			return m_name;
		}

		/**
		 * @return Species primary type for which=0, secondary type for which=1
		 */
		inline EType getType(uint8_t which) const
		{
			assert(which <= 1);
			return m_types[which];
		}

		/**
		 * @return Vector of ability indices this species may have.
		 */
		inline const vector<AbilityID> &getPossibleAbilities(void) const
		{
			return m_possibleAbilities;
		}

		/**
		 * @return Species appearance gender ratio.
		 */
		inline EGenderRatio getGenderRatio(void) const
		{
			return m_genderRatio;
		}

		/**
		 * @return Species catch rate [0..255] where 255 <=> easiest to catch.
		 */
		inline uint8_t getCatchRate(void) const
		{
			return m_catchRate;
		}

		/**
		 * @return Species weight in kg.
		 */
		inline float getWeight(void) const
		{
			return m_weight;
		}

		/**
		 * @return Species base experience point yield.
		 */
		inline uint16_t getBaseExpYield(void) const
		{
			return m_baseExpYield;
		}

		/**
		 * @return Species leveling rate.
		 */
		inline ELevelingRate getLevelingRate(void) const
		{
			return m_levelingRate;
		}

		/**
		 * @return Species effort value yield.
		 */
		inline uint8_t getEVYield(EPrimaryStat stat) const
		{
			return m_evYields[(unsigned) stat];
		}

		/**
		 * @return Species base friendship.
		 */
		inline uint8_t getBaseFriendship(void) const
		{
			return m_baseFriendship;
		}

		/**
		 * @return Species pokedex description text.
		 */
		inline const string &getDescription(void) const
		{
			return m_description;
		}

		/**
		 * @return Species base stats.
		 */
		inline const uint8_t getBaseStat(EPrimaryStat stat) const
		{
			return m_baseStats[(unsigned) stat];
		}

		/**
		 * @return Tuples of <level, vector of move ids to learn> that describe when this species learns which moves.
		 */
		inline const map<Level, vector<MoveID>> &getNaturalMoves(void) const
		{
			return m_naturalMoves;
		}

		/**
		 * @return Indices of TMs this species can learn.
		 */
		inline const vector<TechnicalMachineID> &getCompatibleTMs(void) const
		{
			return m_compatibleTMs;
		}

		/**
		 * @return Indices of HMs this species can learn.
		 */
		inline const vector<HiddenMachineID> &getCompatibleHMs(void) const
		{
			return m_compatibleHMs;
		}

		/**
		 * @return This species' egg group.
		 */
		inline const vector<EEggGroup> getEggGroups(void) const
		{
			return m_eggGroups;
		}

		/**
		 * @return Tuples of <partner species id, vector of learnable move ids> that describe this species' egg moveset.
		 */
		inline const map<SpeciesID, vector<MoveID>> &getEggMoves(void) const
		{
			return m_eggMoves;
		}
	};
}

#endif // SPECIES_H_
