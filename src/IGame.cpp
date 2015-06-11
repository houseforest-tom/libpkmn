/*****************************************************************
 **' PokemonGame.cpp
 *****************************************************************
 **' Created on: 13.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include <IGame.h>

namespace PKMN
{
	IGame::IGame(unsigned windowWidth, unsigned windowHeight, bool fullscreen, const string &title)
	{
		unsigned windowStyle = Style::Close | Style::Titlebar;
		if (fullscreen)
		{
			windowStyle |= Style::Fullscreen;
		}

		m_window.create(VideoMode(windowWidth, windowHeight, 32), title, windowStyle);

		//Setup script interface
		m_scriptInterface.setup();

		//Expose enum types
		exposeEnumTypes();

		//Expose reference types
		exposeReferenceTypes();

		//Expose global variables
		exposeGlobals();
	}

	/*****************************************************************
	 *****************************************************************/

	void IGame::exposeEnumTypes(void)
	{
		//Expose types
		assert(m_scriptInterface.exposeEnumType<EType>("EType",
		{
				{"NORMAL", 		EType::NORMAL},
				{"FIGHTING", 	EType::FIGHTING},
				{"FLYING", 		EType::FLYING},
				{"POISON", 		EType::POISON},
				{"GROUND", 		EType::GROUND},
				{"ROCK", 		EType::ROCK},
				{"BUG", 		EType::BUG},
				{"GHOST", 		EType::GHOST},
				{"STEEL", 		EType::STEEL},
				{"FIRE",		EType::FIRE},
				{"WATER", 		EType::WATER},
				{"GRASS", 		EType::GRASS},
				{"ELECTRIC", 	EType::ELECTRIC},
				{"PSYCHIC", 	EType::PSYCHIC},
				{"ICE", 		EType::ICE},
				{"DRAGON", 		EType::DRAGON},
				{"ELECTRIC", 	EType::ELECTRIC},
				{"DARK", 		EType::DARK},
				{"FAIRY", 		EType::FAIRY},
				{"NONE", 		EType::NONE}
		}));
		assert(m_scriptInterface.exposeGlobalFunction("string tostring(EType)", asFUNCTION(ENUM_TOSTRING_FUNC(EType))));
		assert(m_scriptInterface.exposeGlobal("const uint32 ETYPE_COUNT", (void *)&ENUM_COUNT(EType)));

		//Expose primary stats
		assert(m_scriptInterface.exposeEnumType<EPrimaryStat>("EPrimaryStat",
		{
				{"HP", 		EPrimaryStat::HP},
				{"ATK", 	EPrimaryStat::ATK},
				{"DEF", 	EPrimaryStat::DEF},
				{"SPATK", 	EPrimaryStat::SPATK},
				{"SPDEF", 	EPrimaryStat::SPDEF},
				{"SPEED", 	EPrimaryStat::SPEED}
		}));
		assert(m_scriptInterface.exposeGlobalFunction("string tostring(EPrimaryStat)", asFUNCTION(ENUM_TOSTRING_FUNC(EPrimaryStat))));

		//Expose secondary stats
		assert(m_scriptInterface.exposeEnumType<ESecondaryStat>("ESecondaryStat",
		{
				{"ACCURACY",	ESecondaryStat::ACCURACY},
				{"EVASION", 	ESecondaryStat::EVASION},
				{"CRITICAL", 	ESecondaryStat::CRITICAL}
		}));
		assert(m_scriptInterface.exposeGlobalFunction("string tostring(ESecondaryStat)", asFUNCTION(ENUM_TOSTRING_FUNC(ESecondaryStat))));

		//Expose major status ailments
		assert(m_scriptInterface.exposeEnumType<EMajorStatusAilment>("EMajorStatusAilment",
		{
				{"NONE", 		EMajorStatusAilment::NONE},
				{"SLEEP", 		EMajorStatusAilment::SLEEP},
				{"PARALYSIS", 	EMajorStatusAilment::PARALYSIS},
				{"BURN", 		EMajorStatusAilment::BURN},
				{"POISON", 		EMajorStatusAilment::POISON},
				{"TOXIC", 		EMajorStatusAilment::TOXIC},
				{"FREEZE",		EMajorStatusAilment::FREEZE},
				{"FAINTED", 	EMajorStatusAilment::FAINTED}
		}));
		assert(m_scriptInterface.exposeGlobalFunction("string tostring(EMajorStatusAilment)", asFUNCTION(ENUM_TOSTRING_FUNC(EMajorStatusAilment))));

		//Expose move targets
		assert(m_scriptInterface.exposeEnumType<EMoveTarget>("EMoveTarget",
		{
				{"SINGLE_BESIDES_USER", 		EMoveTarget::SINGLE_BESIDES_USER},
				{"NONE", 						EMoveTarget::NONE},
				{"RANDOM_OPPONENT", 			EMoveTarget::RANDOM_OPPONENT},
				{"ALL_OPPONENTS", 				EMoveTarget::ALL_OPPONENTS},
				{"ALL_BESIDES_USER", 			EMoveTarget::ALL_BESIDES_USER},
				{"USER", 						EMoveTarget::USER},
				{"BOTH_TEAMS", 					EMoveTarget::BOTH_TEAMS},
				{"USER_TEAM", 					EMoveTarget::USER_TEAM},
				{"OPPONENT_TEAM", 				EMoveTarget::OPPONENT_TEAM},
				{"USER_PARTNER", 				EMoveTarget::USER_PARTNER},
				{"USER_OR_USER_PARTNER", 		EMoveTarget::USER_OR_USER_PARTNER},
				{"SINGLE_OPPONENT", 			EMoveTarget::SINGLE_OPPONENT},
				{"DIRECTLY_OPPOSITE_OPPONENT", 	EMoveTarget::DIRECTLY_OPPOSITE_OPPONENT}
		}));
		assert(m_scriptInterface.exposeGlobalFunction("string tostring(EMoveTarget)", asFUNCTION(ENUM_TOSTRING_FUNC(EMoveTarget))));
	}

	/*****************************************************************
	 *****************************************************************/

	void IGame::exposeReferenceTypes(void)
	{
		//Expose type aliases
		assert(m_scriptInterface.exposeTypeAlias("Level", 			"uint8"));
		assert(m_scriptInterface.exposeTypeAlias("StatStage", 		"int16"));
		assert(m_scriptInterface.exposeTypeAlias("StatValue", 		"uint16"));
		assert(m_scriptInterface.exposeTypeAlias("Experience", 		"uint32"));

		assert(m_scriptInterface.exposeTypeAlias("NatureID",  		"uint16"));
		assert(m_scriptInterface.exposeTypeAlias("AbilityID", 		"uint16"));
		assert(m_scriptInterface.exposeTypeAlias("MoveEffectID",	"uint16"));
		assert(m_scriptInterface.exposeTypeAlias("MoveID", 			"uint16"));
		assert(m_scriptInterface.exposeTypeAlias("SpeciesID", 		"uint16"));

		//Expose nature class
		assert(m_scriptInterface.exposeReferenceType<Nature>("Nature"));
		assert(m_scriptInterface.exposeMemberFunction("Nature", "NatureID getID(void) const", asMETHOD(Nature, getID)));
		assert(m_scriptInterface.exposeMemberFunction("Nature", "const string &getName(void) const", asMETHOD(Nature, getName)));
		assert(m_scriptInterface.exposeMemberFunction("Nature", "EPrimaryStat getIncreasedStat(void) const", asMETHOD(Nature, getIncreasedStat)));
		assert(m_scriptInterface.exposeMemberFunction("Nature", "EPrimaryStat getDecreasedStat(void) const", asMETHOD(Nature, getDecreasedStat)));
		assert(m_scriptInterface.exposeMemberFunction("Nature", "bool isNeutral(void) const", asMETHOD(Nature, isNeutral)));
		assert(m_scriptInterface.exposeMemberFunction("Nature", "StatValue calcInfluencedStat(EPrimaryStat, uint16) const", asMETHOD(Nature, calcInfluencedStat)));

		//Expose ability class
		assert(m_scriptInterface.exposeReferenceType<Ability>("Ability"));
		assert(m_scriptInterface.exposeMemberFunction("Ability", "AbilityID getID(void) const", asMETHOD(Ability, getID)));
		assert(m_scriptInterface.exposeMemberFunction("Ability", "const string &getName(void) const", asMETHOD(Ability, getName)));
		assert(m_scriptInterface.exposeMemberFunction("Ability", "const string &getDescription(void) const", asMETHOD(Ability, getDescription)));

		//Expose move class
		assert(m_scriptInterface.exposeReferenceType<Move>("Move"));
		assert(m_scriptInterface.exposeMemberFunction("Move", "MoveID getID(void) const", asMETHOD(Move, getID)));
		assert(m_scriptInterface.exposeMemberFunction("Move", "const string &getName(void) const", asMETHOD(Move, getName)));
		assert(m_scriptInterface.exposeMemberFunction("Move", "MoveEffectID getEffectID(void) const", asMETHOD(Move, getEffectID)));
		assert(m_scriptInterface.exposeMemberFunction("Move", "const string &getDescription(void) const", asMETHOD(Move, getDescription)));

		//Expose moveset class
		assert(m_scriptInterface.exposeReferenceType<Moveset>("Moveset"));
		assert(m_scriptInterface.exposeMemberFunction("Moveset", "MoveID getMoveID(uint8) const", asMETHOD(Moveset, getMoveID)));

		//Expose species class
		assert(m_scriptInterface.exposeReferenceType<Species>("Species"));
		assert(m_scriptInterface.exposeMemberFunction("Species", "SpeciesID getID(void) const", asMETHOD(Species, getID)));
		assert(m_scriptInterface.exposeMemberFunction("Species", "const string &getName(void) const", asMETHOD(Species, getName)));
		assert(m_scriptInterface.exposeMemberFunction("Species", "EType getType(uint8) const", asMETHOD(Species, getType)));
		assert(m_scriptInterface.exposeMemberFunction("Species", "StatValue getBaseStat(EPrimaryStat) const", asMETHOD(Species, getBaseStat)));

		//Expose pokemon class
		assert(m_scriptInterface.exposeReferenceType<Pokemon>("Pokemon"));
		assert(m_scriptInterface.exposeMemberFunction("Pokemon", "Level getLevel(void) const", asMETHOD(Pokemon, getLevel)));
		assert(m_scriptInterface.exposeMemberFunction("Pokemon", "SpeciesID getSpeciesID(void) const", asMETHOD(Pokemon, getSpeciesID)));
		assert(m_scriptInterface.exposeMemberFunction("Pokemon", "const string &getNickname(void) const", asMETHOD(Pokemon, getNickname)));
		assert(m_scriptInterface.exposeMemberFunction("Pokemon", "const Moveset &getMoveset(void) const", asMETHOD(Pokemon, getMoveset)));
		assert(m_scriptInterface.exposeMemberFunction("Pokemon", "StatValue getMaxStat(EPrimaryStat) const", asMETHOD(Pokemon, getMaxStat)));
		assert(m_scriptInterface.exposeMemberFunction("Pokemon", "EMajorStatusAilment getMajorStatusAilment(void) const", asMETHOD(Pokemon, getMajorStatusAilment)));
		assert(m_scriptInterface.exposeMemberFunction("Pokemon", "void setMajorStatusAilment(EMajorStatusAilment)", asMETHOD(Pokemon, setMajorStatusAilment)));

		assert(m_scriptInterface.exposeMemberFunction("Pokemon", "StatStage getStatStage(EPrimaryStat) const", asMETHODPR(
				Pokemon, getStatStage, (EPrimaryStat) const, StatStage
		))); //Get primary stat stage

		assert(m_scriptInterface.exposeMemberFunction("Pokemon", "StatStage getStatStage(ESecondaryStat) const", asMETHODPR(
				Pokemon, getStatStage, (ESecondaryStat) const, StatStage
		))); //Get secondary stat stage

		assert(m_scriptInterface.exposeMemberFunction("Pokemon", "void setStatStage(EPrimaryStat, StatStage)", asMETHODPR(
				Pokemon, setStatStage, (EPrimaryStat, StatStage), void
		))); //Set primary stat stage

		assert(m_scriptInterface.exposeMemberFunction("Pokemon", "void setStatStage(ESecondaryStat, StatStage)", asMETHODPR(
				Pokemon, setStatStage, (ESecondaryStat, StatStage), void
		))); //Set secondary stat stage

		assert(m_scriptInterface.exposeMemberFunction("Pokemon", "StatValue getCurrentStat(EPrimaryStat) const", asMETHODPR(
				Pokemon, getCurrentStat, (EPrimaryStat) const, StatValue
		))); //Get current primary stat

		assert(m_scriptInterface.exposeMemberFunction("Pokemon", "StatValue getCurrentStat(ESecondaryStat) const", asMETHODPR(
				Pokemon, getCurrentStat, (ESecondaryStat) const, StatValue
		))); //Get current secondary stat

		//Expose party class
		assert(m_scriptInterface.exposeReferenceType<Party>("Party"));
		assert(m_scriptInterface.exposeMemberFunction("Party", "Pokemon &getMember(uint32)", asMETHOD(Party, scriptGetMemberMutable)));
		assert(m_scriptInterface.exposeMemberFunction("Party", "const Pokemon &getMember(uint32) const", asMETHOD(Party, scriptGetMemberReadonly)));
		assert(m_scriptInterface.exposeMemberFunction("Party", "uint32 getSize(void) const", asMETHOD(Party, getSize)));

		//Expose database class
		assert(m_scriptInterface.exposeReferenceType<Database>("Database"));
		assert(m_scriptInterface.exposeMemberFunction("Database", "uint32 getSpeciesCount(void) const", asMETHOD(Database, getSpeciesCount)));
		assert(m_scriptInterface.exposeMemberFunction("Database", "uint32 getMoveCount(void) const", asMETHOD(Database, getMoveCount)));
		assert(m_scriptInterface.exposeMemberFunction("Database", "uint32 getAbilityCount(void) const", asMETHOD(Database, getAbilityCount)));
		assert(m_scriptInterface.exposeMemberFunction("Database", "uint32 getNatureCount(void) const", asMETHOD(Database, getNatureCount)));
		assert(m_scriptInterface.exposeMemberFunction("Database", "const Species &getSpecies(SpeciesID) const", asMETHOD(Database, getSpecies)));
		assert(m_scriptInterface.exposeMemberFunction("Database", "const Move &getMove(MoveID) const", asMETHOD(Database, getMove)));
		assert(m_scriptInterface.exposeMemberFunction("Database", "const Ability &getAbility(AbilityID) const", asMETHOD(Database, getAbility)));
		assert(m_scriptInterface.exposeMemberFunction("Database", "const Nature &getNature(NatureID) const", asMETHOD(Database, getNature)));

		//Expose battle class
		assert(m_scriptInterface.exposeReferenceType<Battle>("Battle"));
		assert(m_scriptInterface.exposeMemberFunction("Battle", "Party &getPlayerParty(void)", asMETHODPR(
				Battle, getPlayerParty, (void), Party&)
		)); //Get mutable player party reference

		assert(m_scriptInterface.exposeMemberFunction("Battle", "const Party &getPlayerParty(void) const", asMETHODPR(
				Battle, getPlayerParty, (void) const, const Party&)
		)); //Get readonly player party reference

		assert(m_scriptInterface.exposeMemberFunction("Battle", "Party &getEnemyParty(void)", asMETHODPR(
				Battle, getEnemyParty, (void), Party&)
		)); //Get mutable enemy party reference

		assert(m_scriptInterface.exposeMemberFunction("Battle", "const Party &getEnemyParty(void) const", asMETHODPR(
				Battle, getEnemyParty, (void) const, const Party&)
		)); //Get readonly enemy party reference
	}

	/*****************************************************************
	 *****************************************************************/

	void IGame::exposeGlobals(void)
	{
		//Expose database
		assert(m_scriptInterface.exposeGlobal("Database database", &m_database));
	}

	/*****************************************************************
	 *****************************************************************/

	void IGame::run(void)
	{
		//Seed RNG
		srand(time(nullptr));

		//Run setup logic
		onSetup();

		Event ev;
		Clock timer;

		while (m_window.isOpen())
		{
			//Handle all system events first
			while (m_window.pollEvent(ev))
			{
				if (ev.type == Event::Closed)
				{
					m_window.close();
					break;
				}
			}

			//Invoke update hook
			onUpdate(timer.getElapsedTime().asSeconds());
			timer.restart();

			//Clear screen
			m_window.clear(Color(0, 0, 0));

			//Invoke render hook
			onRender();

			//Update screen
			m_window.display();
		}
	}

	/*****************************************************************
	 *****************************************************************/

	Battle *IGame::getBattle(void)
	{
		if(m_pBattle.get() != nullptr)
		{
			if(m_pBattle->terminated())
			{
				m_pBattle.reset(nullptr);
			}
		}

		return m_pBattle.get();
	}

	/*****************************************************************
	 *****************************************************************/

	void IGame::setBattle(Battle *battle)
	{
		m_pBattle = unique_ptr<Battle>(battle);

		if(battle != nullptr)
		{
			//Expose battle to script interface
			assert(m_scriptInterface.exposeGlobal("Battle battle", battle));
		}
	}

	sf::Time IGame::getElapsedTime(void) const
	{
		return m_elapsedTimeClock.getElapsedTime();
	}

	/*****************************************************************
	 *****************************************************************/

	IGame::~IGame(void)
	{
		m_pBattle.reset(nullptr);
	}
}
