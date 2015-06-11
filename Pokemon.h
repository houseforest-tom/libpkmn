/*****************************************************************
 **' Pokemon.h
 *****************************************************************
 **' Created on: 20.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef POKEMON_H_
#define POKEMON_H_

#include <Move.h>
#include <Database.h>
#include <Dependencies.h>
#include <EPrimaryStat.h>
#include <ESecondaryStat.h>
#include <EMajorStatusAilment.h>
#include <EMinorStatusAilment.h>
#include <ScriptReferenceType.h>

namespace PKMN
{
	/**
	 * Highest level that pokemon can reach.
	 */
	static const Level MAX_LEVEL = 100;

	/**
	 * Min- & max length for pokemon nicknames.
	 */
	static const unsigned NICKNAME_MIN_LENGTH =  2;
	static const unsigned NICKNAME_MAX_LENGTH = 16;

	/**
	 * Maximum IV value per stat.
	 */
	static const IndividualValue MAX_IV = 31;

	/**
	 * Maximum EV value per stat.
	 */
	static const EffortValue MAX_EV = 255;

	/**
	 * Maximum overall EV.
	 */
	static const unsigned MAX_OVERALL_EV = 510;

	/**
	 * Represents an instance of a pokemon.
	 */
	class Pokemon : public IPrintable, public ScriptReferenceType
	{
	private:

		/**
		 * Reference to database.
		 */
		const Database &m_db;

		/**
		 * ID of this pokemon's species.
		 */
		SpeciesID m_speciesID;

		/**
		 * This pokemon's nickname.
		 */
		Name m_nickname;

		/**
		 * ID of this pokemon's nature.
		 */
		NatureID m_natureID;

		/**
		 * ID of this pokemon's ability.
		 */
		AbilityID m_abilityID;

		/**
		 * Level.
		 */
		Level m_level;

		/**
		 * Total experience points.
		 */
		Experience m_experience;

		/**
		 * This pokemon's moveset.
		 */
		Moveset m_moveset;

		/**
		 * Individiual values.
		 */
		IndividualValue m_IVs[ENUM_COUNT(EPrimaryStat)];

		/**
		 * Effort values.
		 */
		EffortValue m_EVs[ENUM_COUNT(EPrimaryStat)];

		/**
		 * Maximum stats.
		 */
		StatValue m_maxStats[ENUM_COUNT(EPrimaryStat)];

		/**
		 * Current primary stat stages.
		 * HP stat stage corresponds to amount of HP lost.
		 */
		StatStage m_primaryStatStages[ENUM_COUNT(EPrimaryStat)];

		/**
		 * Current secondary stat stages.
		 */
		StatStage m_secondaryStatStages[ENUM_COUNT(ESecondaryStat)];

		/**
		 * Major status ailment.
		 */
		EMajorStatusAilment m_majorStatusAilment;

		/**
		 * Minor status ailments.
		 */
		vector<EMinorStatusAilment> m_minorStatusAilments;

		/**
		 * Update this pokemon's maximum stats.
		 * Should be invoked after change of nature,
		 * base stats i.e. species ID, level, I-/EVs.
		 */
		void updateMaxStats(void);

	public:

		/**
		 * Construct a new pokemon of the given species.
		 * Ability and nature will be chosen at random from all valid options.
		 * Moveset will contain the last 4 moves learnt up until the specified level.
		 *
		 * @param db
		 * Database const reference.
		 *
		 * @param species
		 * Species ID of the pokemon.
		 *
		 * @param level
		 * Level of the pokemon, 1 if not specified.
		 */
		Pokemon(const Database &db, SpeciesID species, Level level = 1);

		/**
		 * @return Species ID.
		 */
		inline SpeciesID getSpeciesID(void) const
		{
			return m_speciesID;
		}

		/**
		 * Change the pokemon's species ID.
		 *
		 * @param species
		 * New species ID.
		 */
		inline void setSpeciesID(SpeciesID species)
		{
			m_speciesID = species;
			updateMaxStats();
		}

		/**
		 * @return Nature ID.
		 */
		inline NatureID getNatureID(void) const
		{
			return m_natureID;
		}

		/**
		 * Change the pokemon's nature ID.
		 *
		 * @param nature
		 * New nature ID.
		 */
		inline void setNatureID(NatureID nature)
		{
			m_natureID = nature;
			updateMaxStats();
		}

		/**
		 * @return Ability ID.
		 */
		inline AbilityID getAbilityID(void) const
		{
			return m_abilityID;
		}

		/**
		 * @return Level of the pokemon.
		 */
		inline Level getLevel(void) const
		{
			return m_level;
		}

		/**
		 * Change the pokemon's level.
		 * This handles all possible consequences for the moveset,
		 * evolutionary stage, etc.
		 *
		 * @param level
		 * New level. Must be in range [1..MAX_LEVEL].
		 */
		void setLevel(Level level);

		/**
		 * @return Nickname of the pokemon.
		 */
		inline const string &getNickname(void) const
		{
			return m_nickname;
		}

		/**
		 * Change the pokemon's nickname.
		 *
		 * @param nickname
		 * The new nickname.
		 */
		inline void setNickname(const string &nickname)
		{
			assert(nickname.length() >= NICKNAME_MIN_LENGTH && nickname.length() <= NICKNAME_MAX_LENGTH);
			m_nickname.assign(nickname);
		}

		/**
		 * @return Total accumulated amount of experience.
		 */
		inline Experience getExperience(void) const
		{
			return m_experience;
		}

		/**
		 * Add experience points.
		 * If this leads to a level up, the required actions are taken.
		 *
		 * @param exp
		 * The amount of experience points to add.
		 */
		void addExperience(Experience exp);

		/**
		 * @return Moveset.
		 */
		inline const Moveset &getMoveset(void) const
		{
			return m_moveset;
		}

		/**
		 * Overwrite the moveset of this pokemon.
		 *
		 * @param moveset
		 * The new moveset.
		 */
		inline void setMoveset(const Moveset &moveset)
		{
			m_moveset = moveset;
		}

		/**
		 * Return the individual value for the given stat.
		 *
		 * @param stat
		 * The primary stat identifier.
		 *
		 * @return
		 * The individual value (IV).
		 */
		inline IndividualValue getIV(EPrimaryStat stat) const
		{
			return m_IVs[(unsigned) stat];
		}

		/**
		 * Set the individual value for the given stat.
		 *
		 * @param stat
		 * The primary stat.
		 *
		 * @param iv
		 * The individual value (IV).
		 */
		inline void setIV(EPrimaryStat stat, IndividualValue iv)
		{
			assert(iv <= MAX_IV);
			m_IVs[(unsigned) stat] = iv;
			updateMaxStats();
		}

		/**
		 * Return the effort value for the given stat.
		 *
		 * @param stat
		 * The primary stat identifier.
		 *
		 * @return
		 * The effort value (EV).
		 */
		inline EffortValue getEV(EPrimaryStat stat) const
		{
			return m_EVs[(unsigned) stat];
		}

		/**
		 * Set the effort value for the given stat.
		 *
		 * @param stat
		 * The primary stat.
		 *
		 * @param ev
		 * The effort value (EV).
		 */
		inline void setEV(EPrimaryStat stat, EffortValue ev)
		{
			assert(ev <= MAX_EV);
			m_EVs[(unsigned) stat] = ev;
			updateMaxStats();
		}

		/**
		 * Return the maximum value of a primary stat.
		 *
		 * @param stat
		 * The primary stat identifier.
		 *
		 * @return
		 * The maximum stat value.
		 */
		inline StatValue getMaxStat(EPrimaryStat stat) const
		{
			return m_maxStats[(unsigned) stat];
		}

		/**
		 * Return the current stat stage of the given primary stat.
		 *
		 * @param stat
		 * The primary stat identifier.
		 *
		 * @return
		 * The stat stage [-6..6] for stat != HP.
		 * Else HP lost.
		 */
		inline StatStage getStatStage(EPrimaryStat stat) const
		{
			return m_primaryStatStages[(unsigned) stat];
		}

		/**
		 * Set the current stat stage of the given primary stat.
		 *
		 * @param stat
		 * The primary stat.
		 *
		 * @param stage
		 * The stat stage [-6..6].
		 */
		inline void setStatStage(EPrimaryStat stat, StatStage stage)
		{
			//Check range
			if(stat != EPrimaryStat::HP)
			{
				assert(stage >= -6 && stage <= 6);
			}
			else
			{
				assert(stage >= 0 && stage <= getMaxStat(EPrimaryStat::HP)); //0 <=> full HP
			}

			m_primaryStatStages[(unsigned) stat] = stage;
		}

		/**
		 * Return the current stat stage of the given secondary stat.
		 *
		 * @param stat
		 * The secondary stat identifier.
		 *
		 * @return
		 * The stat stage [-6..6].
		 */
		inline StatStage getStatStage(ESecondaryStat stat) const
		{
			return m_secondaryStatStages[(unsigned) stat];
		}

		/**
		 * Set the current stat stage of the given secondary stat.
		 *
		 * @param stat
		 * The secondary stat.
		 *
		 * @param stage
		 * The stat stage [-6..6].
		 * Or [0..Maximum HP] for stat <=> HP, where 0 <=> full HP.
		 */
		inline void setStatStage(ESecondaryStat stat, StatStage stage)
		{
			assert(stage >= -6 && stage <= 6);
			m_secondaryStatStages[(unsigned) stat] = stage;
		}

		/**
		 * Calculate and return the current value of a primary stat.
		 *
		 * @param stat
		 * The primary stat identifier.
		 *
		 * @return
		 * The current stat value.
		 */
		StatValue getCurrentStat(EPrimaryStat stat) const;

		/**
		 * Calculate and return the current value of a secondary stat.
		 *
		 * @param stat
		 * The secondary stat identifier.
		 *
		 * @return
		 * The current stat value.
		 */
		StatValue getCurrentStat(ESecondaryStat stat) const;

		/**
		 * @return Current major status ailment.
		 */
		inline EMajorStatusAilment getMajorStatusAilment(void) const
		{
			return m_majorStatusAilment;
		}

		/**
		 * Set the current major status ailment.
		 *
		 * @param ailment
		 * The major status ailment.
		 */
		inline void setMajorStatusAilment(EMajorStatusAilment ailment)
		{
			m_majorStatusAilment = ailment;
		}

		/**
		 * @return List of all minor status ailments this pokemon suffers from.
		 */
		inline const vector<EMinorStatusAilment> &getMinorStatusAilments(void) const
		{
			return m_minorStatusAilments;
		}

		/**
	     * Overwrite all minor status ailments with the list provided.
	     *
		 * @param ailments
		 * List of minory status ailments to apply.
		 */
		inline void setMinorStatusAilments(const vector<EMinorStatusAilment> ailments)
		{
			m_minorStatusAilments = ailments;
		}

		/**
		 * Adds the specified minor status ailment to this pokemon's list.
		 * If the pokemon already suffers from this ailment, nothing happens.
		 *
		 * @param ailment
		 * The minor status ailment to add.
		 */
		inline void addMinorStatusAilment(EMinorStatusAilment ailment)
		{
			if(invector(m_minorStatusAilments, ailment)) return;
			m_minorStatusAilments.push_back(ailment);
		}

		/**
		 * Removes the specified minor status ailment from this pokemon's list.
		 * If the pokemon does not currently suffer from this ailment, nothing happens.
		 *
		 * @param ailment
		 * The minor status ailment to remove.
		 */
		inline void removeMinorStatusAilment(EMinorStatusAilment ailment)
		{
			auto iter = find(m_minorStatusAilments.begin(), m_minorStatusAilments.end(), ailment);
			if(iter == m_minorStatusAilments.end()) return;
			m_minorStatusAilments.erase(iter);
		}

		/**
		 * Restore all current stats to their maximum value,
		 * that is by resetting all stat stages to 0.
		 */
		void restoreStats(void);

		/**
		 * Print pokemon information.
		 */
		void print(void) const;
	};
}

#endif // POKEMON_H_
