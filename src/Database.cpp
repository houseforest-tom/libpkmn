/*****************************************************************
 **' Database.cpp
 *****************************************************************
 **' Created on: 20.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include <Database.h>

namespace PKMN
{
	Database::Database(void)
	{
		NOOP;
	}

	/*****************************************************************
	 *****************************************************************/

	void Database::storeNature(const Nature &nature)
	{
		m_natures.insert({nature.getID(), nature});
	}

	/*****************************************************************
	 *****************************************************************/

	void Database::storeAbility(const Ability &ability)
	{
		m_abilities.insert({ability.getID(), ability});
	}

	/*****************************************************************
	 *****************************************************************/

	void Database::storeMoveEffect(const MoveEffect &effect)
	{
		m_moveEffects.insert({effect.getID(), effect});
	}

	/*****************************************************************
	 *****************************************************************/

	void Database::storeMove(const Move &move)
	{
		m_moves.insert({move.getID(), move});
	}

	/*****************************************************************
	 *****************************************************************/

	void Database::storeSpecies(const Species &species)
	{
		m_species.insert({species.getID(), species});
	}

	/*****************************************************************
	 *****************************************************************/

	const Nature &PKMN::Database::getNature(NatureID id) const
	{
		assert(m_natures.count(id) == 1);
		return m_natures.at(id);
	}

	/*****************************************************************
	 *****************************************************************/

	unsigned Database::getNatureCount(void) const
	{
		return m_natures.size();
	}

	/*****************************************************************
	 *****************************************************************/

	const PKMN::Ability &Database::getAbility(AbilityID id) const
	{
		assert(m_abilities.count(id) == 1);
		return m_abilities.at(id);
	}

	/*****************************************************************
	 *****************************************************************/

	unsigned Database::getAbilityCount(void) const
	{
		return m_abilities.size();
	}

	/*****************************************************************
	 *****************************************************************/

	const MoveEffect &Database::getMoveEffect(MoveEffectID id) const
	{
		assert(m_moveEffects.count(id) == 1);
		return m_moveEffects.at(id);
	}

	/*****************************************************************
	 *****************************************************************/

	const PKMN::Move &Database::getMove(MoveID id) const
	{
		assert(m_moves.count(id) == 1);
		return m_moves.at(id);
	}

	/*****************************************************************
	 *****************************************************************/

	unsigned Database::getMoveEffectCount(void) const
	{
		return m_moveEffects.size();
	}

	/*****************************************************************
	 *****************************************************************/

	unsigned Database::getMoveCount(void) const
	{
		return m_moves.size();
	}

	/*****************************************************************
	 *****************************************************************/

	const PKMN::Species &Database::getSpecies(SpeciesID id) const
	{
		assert(m_species.count(id) == 1);
		return m_species.at(id);
	}

	/*****************************************************************
	 *****************************************************************/

	unsigned Database::getSpeciesCount(void) const
	{
		return m_species.size();
	}

	/*****************************************************************
	 *****************************************************************/

	int Database::loadSpeciesFromFile(const Filename &file)
	{
		//Try open the file
		ifstream filestream(file);
		if(!filestream.good())
		{
			//File not found
			return -1;
		}

		int count = 0;
		string line;
		while(!filestream.eof())
		{
			try
			{
				/** !Load next species! */

				//Read ID
				getline(filestream, line);
				SpeciesID speciesID = atoi(line.c_str());

				//Read name
				getline(filestream, line);
				Name name = line;

				//Read primary type
				getline(filestream, line);
				EType primaryType = (EType)atoi(line.c_str());

				//Read secondary type
				getline(filestream, line);
				EType secondaryType = (EType)atoi(line.c_str());

				//Read abilities
				getline(filestream, line);
				vector<AbilityID> abilities;
				for(const auto &value : splitstr(line, ','))
				{
					abilities.push_back(atoi(value.c_str()));
				}

				//Read gender ratio
				getline(filestream, line);
				EGenderRatio genderRatio = (EGenderRatio)atoi(line.c_str());

				//Read catch rate
				getline(filestream, line);
				CatchRate catchRate = CatchRate(atoi(line.c_str()));

				//Read weight
				getline(filestream, line);
				float weight = atof(line.c_str());

				//Read XP yield
				getline(filestream, line);
				Experience expYield = Experience(atoi(line.c_str()));

				//Read leveling rate
				getline(filestream, line);
				ELevelingRate levelingRate = (ELevelingRate)atoi(line.c_str());

				//Read EV yields
				getline(filestream, line);
				vector<EffortValue> evYields;
				for(const auto &value : splitstr(line, ','))
				{
					evYields.push_back(EffortValue(atoi(value.c_str())));
				}

				//Read base friendship
				getline(filestream, line);
				FriendshipValue baseFriendship = FriendshipValue(atoi(line.c_str()));

				//Read description
				getline(filestream, line);
				DescriptionText desc = DescriptionText(line);

				//Read base stats
				getline(filestream, line);
				vector<BaseStatValue> baseStats;
				for(const auto &value : splitstr(line, ','))
				{
					baseStats.push_back(BaseStatValue(atoi(value.c_str())));
				}

				/*
				 * Read natural (levelup) moves.
				 * Format for natural moves is as follows:
				 * LEVEL:MOVE,MOVE,MOVE;LEVEL:MOVE,MOVE
				 */
				getline(filestream, line);
				map<Level, vector<MoveID>> naturalMoves;
				vector<string> levelSplit = splitstr(line, ';');
				for(const auto &part : levelSplit)
				{
					//First part is level
					string levelStr = splitstr(part, ':')[0];
					Level  level = Level(atoi(levelStr.c_str()));

					//Second part is list of move IDs
					string LevelMovesStr = splitstr(part, ':')[1];
					vector<string> moveIDstrs = splitstr(LevelMovesStr, ',');

					//Read move IDs
					vector<MoveID> moveIDs;
					for(const auto &moveIDstr : moveIDstrs)
					{
						moveIDs.push_back(MoveID(atoi(moveIDstr.c_str())));
					}

					//Insert constructed pair
					naturalMoves.insert({level, moveIDs});
				}

				//Read compatible TMs
				getline(filestream, line);
				vector<TechnicalMachineID> compatTMs;
				for(const auto &value : splitstr(line, ','))
				{
					compatTMs.push_back(TechnicalMachineID(atoi(value.c_str())));
				}

				//Read compatible HMs
				getline(filestream, line);
				vector<HiddenMachineID> compatHMs;
				for(const auto &value : splitstr(line, ','))
				{
					compatHMs.push_back(HiddenMachineID(atoi(value.c_str())));
				}

				//Read egg groups
				getline(filestream, line);
				vector<EEggGroup> eggGroups;
				for(const auto &value : splitstr(line, ','))
				{
					eggGroups.push_back((EEggGroup)atoi(value.c_str()));
				}

				/*
				 * Read egg moves.
				 * Format for egg moves is as follows:
				 * SPECIES:MOVE,MOVE,MOVE;SPECIES:MOVE,MOVE
				 */
				getline(filestream, line);
				map<SpeciesID, vector<MoveID>> eggMoves;
				vector<string> speciesSplit = splitstr(line, ';');
				for(const auto &part : speciesSplit)
				{
					//First part is species ID
					string speciesIDStr = splitstr(part, ':')[0];
					SpeciesID speciesID = SpeciesID(atoi(speciesIDStr.c_str()));

					//Second part is list of move IDs
					string speciesMovesStr = splitstr(part, ':')[1];
					vector<string> moveIDstrs = splitstr(speciesMovesStr, ',');

					//Read move IDs
					vector<MoveID> moveIDs;
					for(const auto &moveIDstr : moveIDstrs)
					{
						moveIDs.push_back(MoveID(atoi(moveIDstr.c_str())));
					}

					//Insert constructed pair
					eggMoves.insert({speciesID, moveIDs});
				}

				/*
				 * Read evolutions.
				 * Format is CONDITION,PARAM,SPECIES.
				 * If no parameters are taken: CONDITION,,SPECIES.
				 */
				getline(filestream, line);
				vector<Evolution> evolutions;
				vector<string> args = splitstr(line, ',');
				for(unsigned i=0; i<args.size(); i+=3)
				{
					//Condition type, Parameter value, Target species.
					Evolution evo;
					evo.condition = (EEvolutionCondition)atoi(args[i+0].c_str());
					evo.param = EvolutionParam(atoi(args[i+1].c_str()));
					evo.species = SpeciesID(atoi(args[i+2].c_str()));
					evolutions.push_back(evo);
				}

				//Construct species from read values and store it in the database
				storeSpecies(Species(speciesID, name, {primaryType, secondaryType}, abilities, genderRatio, catchRate,
									 weight, expYield, levelingRate, evYields, baseFriendship, desc, baseStats,
									 naturalMoves, compatTMs, compatHMs, eggGroups, eggMoves, evolutions));

				//Skip one line
				if(!filestream.eof())
				{
					getline(filestream, line);
				}

				++count;
			}
			catch(...)
			{
				//IO-Exception
				return -1;
			}
		}

		//Success!
		filestream.close();
		return count;
	}

	/*****************************************************************
	 *****************************************************************/

	void Database::print(void) const
	{
		cout << "<Database>" << endl;
		cout << "\t" << endl;
		cout << "</Database>" << endl << endl;
	}
}
