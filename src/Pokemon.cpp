/*****************************************************************
 **' Pokemon.cpp
 *****************************************************************
 **' Created on: 20.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include <Pokemon.h>
#include <Database.h>
#include <memory.h>

namespace PKMN
{
	Pokemon::Pokemon(const Database &db, SpeciesID species, Level level)
			: m_db(db), m_majorStatusAilment(EMajorStatusAilment::NONE), m_minorStatusAilments({})
	{
		//Set species ID
		assert(species > 0 && species <= db.getSpeciesCount());
		m_speciesID = species;

		//Set level
		assert(level <= MAX_LEVEL);
		m_level = level;

		//Set experience
		//TODO: get experience from LUT
		m_experience = level * 1000;

		//Set random nature
		m_natureID = 1 + (rand() % db.getNatureCount());

		//Acquire species data from DB
		const Species &speciesData = db.getSpecies(species);

		//Set default nickname
		m_nickname.assign(speciesData.getName());

		//Choose ability
		const vector<AbilityID> &abilities = speciesData.getPossibleAbilities();
		m_abilityID = abilities[rand() % abilities.size()];

		//Add moves to moveset
		unsigned slot = 0;
		const map<Level, vector<MoveID>> &moves = speciesData.getNaturalMoves();
		for (auto iter = moves.begin(); iter != moves.end(); ++iter)
		{
			//Level is below this pokemon's level
			if (iter->first <= level)
			{
				//Teach all moves learnt at this level
				for (unsigned i = 0; i < iter->second.size(); ++i)
				{
					m_moveset[slot++ % MOVESET_SIZE] = iter->second[i];
				}
			}
		}

		//Set EVs to 0
		memset(m_EVs, 0, sizeof(m_EVs));

		//Set IVs to random values
		for (unsigned stat = 0; stat < ENUM_COUNT(EPrimaryStat); ++stat)
		{
			m_IVs[stat] = rand() % (MAX_IV + 1);
		}

		//Set stat stages to zero
		restoreStats();

		//Calculate maximum stats
		updateMaxStats();
	}

	/*****************************************************************
	 *****************************************************************/

	void Pokemon::restoreStats(void)
	{
		memset(m_primaryStatStages, 0, sizeof(m_primaryStatStages));
		memset(m_secondaryStatStages, 0, sizeof(m_secondaryStatStages));
	}

	/*****************************************************************
	 *****************************************************************/

	void Pokemon::updateMaxStats(void)
	{
		//HP   = floor(NATURE * floor((2 * BASE + IV + EV / 4 + 100) * LEVEL / 100 + 10))
		//Stat = floor(NATURE * floor((2 * BASE + IV + EV / 4) * LEVEL / 100 + 5))

		const Species &species = m_db.getSpecies(m_speciesID);
		const Nature &nature = m_db.getNature(m_natureID);

		uint8_t base;  //Base stat
		uint8_t iv;	   //Individual value
		uint8_t ev;	   //Effort value
		double temp;   //Stat value before nature influence

		for (unsigned stat = 0; stat < ENUM_COUNT(EPrimaryStat); ++stat)
		{
			//If base stat is 1 => max stat is 1 as well
			if ((base = species.getBaseStat((EPrimaryStat) stat)) == 1)
			{
				m_maxStats[stat] = 1;
			}
			else
			{
				iv = m_IVs[stat];
				ev = m_EVs[stat];

				//Find temporary stat value (no nature influence yet)
				temp = floor(2.0 * base + iv + ev / 4);
				if ((EPrimaryStat)stat == EPrimaryStat::HP) temp += 100;
				temp *= m_level / 100.0;
				temp += ((EPrimaryStat) stat == EPrimaryStat::HP ? 10 : 5);

				//Calculate stat after nature influence
				m_maxStats[stat] = (uint16_t) floor(nature.calcInfluencedStat((EPrimaryStat) stat, (uint16_t) temp));
			}
		}
	}

	/*****************************************************************
	 *****************************************************************/

	uint16_t Pokemon::getCurrentStat(EPrimaryStat stat) const
	{
		//Primary stat stage multipliers ordered from -6 to +6
		static double multipliers[] = {
				2.0 / 8.0,
				2.0 / 7.0,
				2.0 / 6.0,
				2.0 / 5.0,
				2.0 / 4.0,
				2.0 / 3.0,
				2.0 / 2.0,
				3.0 / 2.0,
				4.0 / 2.0,
				5.0 / 2.0,
				6.0 / 2.0,
				7.0 / 2.0,
				8.0 / 2.0
		};

		int stage = (int) m_primaryStatStages[(unsigned) stat];

		//Calculate current HP := max HP - stat stage
		if (stat == EPrimaryStat::HP)
		{
			return getMaxStat(stat) - m_primaryStatStages[(unsigned) stat];
		}

		//Calculate current other stat using multiplier array
		else
		{
			return (uint16_t) floor((double) m_maxStats[(unsigned) stat] * multipliers[stage + 6]);
		}
	}

	/*****************************************************************
	 *****************************************************************/

	uint16_t Pokemon::getCurrentStat(ESecondaryStat stat) const
	{
		//Secondary stat stage multipliers ordered from -6 to +6
		static double multipliers[] = {
				3.0 / 9.0,
				3.0 / 8.0,
				3.0 / 7.0,
				3.0 / 6.0,
				3.0 / 5.0,
				3.0 / 4.0,
				3.0 / 3.0,
				4.0 / 3.0,
				5.0 / 3.0,
				6.0 / 3.0,
				7.0 / 3.0,
				8.0 / 3.0,
				9.0 / 3.0
		};

		int8_t stage = m_secondaryStatStages[(unsigned) stat];
		return (uint16_t) floor(100.0 * multipliers[stage + 6]);
	}

	/*****************************************************************
	 *****************************************************************/

	void Pokemon::addExperience(uint32_t exp)
	{
		m_experience += exp;

		//TODO: handle level ups according to experience LUT
	}

	/*****************************************************************
	 *****************************************************************/

	void Pokemon::setLevel(uint8_t level)
	{
		assert(level <= MAX_LEVEL);
		m_level = level;

		updateMaxStats();

		//TODO: handle learning of moves and possible evolutions at this level
	}

	/*****************************************************************
	 *****************************************************************/

	void Pokemon::print(void) const
	{
		cout << "<Pokemon>" << endl;

		cout << "Species:\t\t" << m_db.getSpecies(m_speciesID).getName() << endl;
		cout << "Level:\t\t\t" << formatstr("%03u", m_level) << endl;
		cout << "Ability:\t\t" << m_db.getAbility(m_abilityID).getName() << endl;
		cout << "Nature:\t\t\t" << m_db.getNature(m_natureID).getName() << endl;

		cout << "Mj. Status Ailment:\t" << ENUM_STRING(EMajorStatusAilment, m_majorStatusAilment) << endl;
		cout << "Mn. Status Ailments:\t";
		for(unsigned ailment = 0; ailment < m_minorStatusAilments.size(); ailment++)
		{
			cout << ENUM_STRING(EMinorStatusAilment, m_minorStatusAilments[ailment]) << ", ";
		}
		cout << endl;

		cout << "Moveset:\t\t";
		for (unsigned move = 0; move < MOVESET_SIZE; ++move)
		{
			MoveID moveID = m_moveset[move];
			if (moveID == 0) cout << "----";
			else cout << (m_db.getMoveCount() >= moveID ? m_db.getMove(moveID).getName() : formatstr("%03u", moveID)) << ", ";
		}
		cout << endl;

		cout << "Stats:" << endl;
		for (unsigned stat = 0; stat < ENUM_COUNT(EPrimaryStat); ++stat)
		{
			EPrimaryStat stat_e = (EPrimaryStat) stat;
			cout << "\t\t\t" << ENUM_STRING(EPrimaryStat, stat_e) << ":\t";
			cout << formatstr("%4u/%4u", getCurrentStat(stat_e), getMaxStat(stat_e));
			cout << " ";
			cout << formatstr("(Stage: %+1d, IV: %2u, EV: %3u)",
					getStatStage(stat_e),
					getIV(stat_e),
					getEV(stat_e));
			cout << endl;
		}

		cout << "</Pokemon>" << endl << endl;
	}
}
