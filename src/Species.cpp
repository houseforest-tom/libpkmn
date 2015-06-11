/*****************************************************************
 **' PokemonSpecies.cpp
 *****************************************************************
 **' Created on: 15.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include <Species.h>
#include <cstring>	  //memcpy

namespace PKMN
{
	Species::Species(SpeciesID id, const Name &name, const vector<EType> &types, const vector<AbilityID> &abilities,
			EGenderRatio genderRatio, CatchRate catchRate, float weight, Experience baseExpYield, ELevelingRate lvlRate,
			const vector<EffortValue> &evYields, FriendshipValue baseFriendship, const DescriptionText &desc,
			const vector<BaseStatValue> &base, const map<Level, vector<MoveID>> &naturalMoves,
			const vector<TechnicalMachineID> &compatTM, const vector<HiddenMachineID> &compatHM,
			const vector<EEggGroup> &eggGroups, const map<SpeciesID, vector<MoveID>> &eggMoves,
			const vector<Evolution> &evolutions)
			:
					//Initializer list used for members that don't need validity check
					m_genderRatio(genderRatio), m_catchRate(catchRate), m_baseExpYield(baseExpYield), m_levelingRate(lvlRate),
					m_baseFriendship(baseFriendship), m_compatibleTMs(compatTM), m_compatibleHMs(compatHM), m_eggGroups(eggGroups),
					m_eggMoves(eggMoves), m_evolutions(evolutions)
	{
		//Validate rest of input parameters
		assert(id > 0);											//Only accept IDs > 0
		assert(name.length() > 0);								//Only accept non-empty names

		assert(types.size() >= 1 && types.size() <= 2); 		//Only accept 1 or 2 specified types

		if (types.size() == 2)
		{
			assert(types[0] != types[1]);						//Do not accept 2x the same type as primary and secondary
		}

		assert(abilities.size() >= 1);							//Require atleast one possible ability
		assert(weight > 0);										//Only accept positive non-zero weights
		assert(evYields.size() == ENUM_COUNT(EPrimaryStat));	//Assert correct EV value vector
		assert(desc.length() > 0);								//Only accept non-empty pokedex description texts
		assert(base.size() == ENUM_COUNT(EPrimaryStat));		//Assert corret base stat vector
		assert(naturalMoves.count(1) > 0);						//Require atleast one move learned from level 1 on to prevent empty movesets

		//Assign integral values
		m_ID = id;
		m_weight = weight;
		m_types[0] = types[0];
		m_types[1] = (types.size() == 2 ? types[1] : EType::NONE);

		//Assign string values
		m_name.assign(name);
		m_description.assign(desc);

		//Assign container contents
		m_possibleAbilities = abilities;
		m_naturalMoves = naturalMoves;

		//Fill arrays
		memcpy(m_baseStats, &base[0], 	 ENUM_COUNT(EPrimaryStat) * sizeof(base[0]));
		memcpy(m_evYields, &evYields[0], ENUM_COUNT(EPrimaryStat) * sizeof(evYields[0]));
	}

	/*****************************************************************
	 *****************************************************************/

	void Species::print(void) const
	{
		cout << "<Pokemon Species>" << endl;
		cout << "ID:\t\t\t" << m_ID << endl;
		cout << "Name:\t\t\t" << m_name << endl;
		cout << "Type:\t\t\t" << ENUM_STRING(EType, m_types[0]) << "/" << ENUM_STRING(EType, m_types[1]) << endl;
		cout << "Weight:\t\t\t" << m_weight << "kg" << endl;
		cout << "Leveling Rate:\t\t" << ENUM_STRING(ELevelingRate, m_levelingRate) << endl;
		cout << "EXP Yield:\t\t" << m_baseExpYield << endl;
		cout << "Base Friendship:\t" << formatstr("%03u", m_baseFriendship) << endl;
		cout << "Catch Rate:\t\t" << formatstr("%03u", m_catchRate) << endl;
		cout << "Gender Ratio:\t\t" << ENUM_STRING(EGenderRatio, m_genderRatio) << endl;

		cout << "Egg groups:\t\t";
		for (auto iter = m_eggGroups.begin(); iter != m_eggGroups.end(); ++iter)
			cout << ENUM_STRING(EEggGroup, *iter) << ", ";
		cout << endl;

		cout << "Abilities:\t\t";
		for (auto iter = m_possibleAbilities.begin(); iter != m_possibleAbilities.end(); ++iter)
			cout << *iter << ", ";
		cout << endl;

		cout << "Base Stats:\t\t";
		for (unsigned stat = 0; stat < ENUM_COUNT(EPrimaryStat); ++stat)
			cout << formatstr("%03u", m_baseStats[stat]) << ", ";
		cout << endl;

		cout << "EV Yield:\t\t";
		for (unsigned stat = 0; stat < ENUM_COUNT(EPrimaryStat); ++stat)
			cout << formatstr(" %01u,  ", m_evYields[stat]);
		cout << endl;

		cout << "Moves to learn:\t" << endl;
		for (auto iter = m_naturalMoves.begin(); iter != m_naturalMoves.end(); ++iter)
		{
			cout << "\t\t\tLevel: " << formatstr("%03u", iter->first) << " -> Moves: ";
			for (unsigned move = 0; move < iter->second.size(); ++move)
				cout << iter->second[move] << ", ";
			cout << endl;
		}

		cout << "Compatible TMs:\t\t";
		for (auto iter = m_compatibleTMs.begin(); iter != m_compatibleTMs.end(); ++iter)
			cout << *iter << ", ";
		cout << endl;

		cout << "Compatible HMs:\t\t";
		for (auto iter = m_compatibleHMs.begin(); iter != m_compatibleHMs.end(); ++iter)
			cout << *iter << ", ";
		cout << endl;

		cout << "Evolutions:" << endl;
		for(unsigned i=0; i<m_evolutions.size(); i++)
		{
			cout << "\t\t\tCondition:\t" << (unsigned)m_evolutions[i].condition << endl;
			cout << "\t\t\tParameter:\t" << m_evolutions[i].param	  << endl;
			cout << "\t\t\tSpecies:\t"   << m_evolutions[i].species   << endl;
		}

		cout << "Pokedex Desc:\t\t" << m_description << endl;
		cout << "</Pokemon Species>" << endl << endl;
	}
}
