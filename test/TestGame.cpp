/*****************************************************************
 **' TestPokemonGame.cpp
 *****************************************************************
 **' Created on: 15.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include <TestGame.h>
#include <Party.h>
#include <Battle.h>
#include <DefaultBattleMechanics.h>

namespace PKMN
{
	TestGame::TestGame(void)
			: IGame(1280, 720, false, "Test Pokemon Game")
	{
		NOOP;
	}

	/*****************************************************************
	 *****************************************************************/

	void TestGame::createNatures(void)
	{
		Database &db = getDatabase();

		//Neutral natures
		db.storeNature(Nature::createNeutral(NatureID(0x01), Name("HARDY")));
		db.storeNature(Nature::createNeutral(NatureID(0x02), Name("DOCILE")));
		db.storeNature(Nature::createNeutral(NatureID(0x03), Name("BASHFUL")));
		db.storeNature(Nature::createNeutral(NatureID(0x04), Name("QUIRKY")));
		db.storeNature(Nature::createNeutral(NatureID(0x05), Name("SERIOUS")));

		//+ATK natures
		db.storeNature(Nature(NatureID(0x06), Name("LONELY"), 	EPrimaryStat::ATK, 	 	EPrimaryStat::DEF));
		db.storeNature(Nature(NatureID(0x07), Name("ADAMANT"), 	EPrimaryStat::ATK, 	 	EPrimaryStat::SPATK));
		db.storeNature(Nature(NatureID(0x08), Name("NAUGHTY"), 	EPrimaryStat::ATK, 	 	EPrimaryStat::SPDEF));
		db.storeNature(Nature(NatureID(0x09), Name("BRAVE"), 	EPrimaryStat::ATK, 	 	EPrimaryStat::SPEED));

		//+DEF natures
		db.storeNature(Nature(NatureID(0x0A), Name("BOLD"), 	EPrimaryStat::DEF, 	 	EPrimaryStat::ATK));
		db.storeNature(Nature(NatureID(0x0B), Name("IMPISH"), 	EPrimaryStat::DEF, 	 	EPrimaryStat::SPATK));
		db.storeNature(Nature(NatureID(0x0C), Name("LAX"), 		EPrimaryStat::DEF, 	 	EPrimaryStat::SPDEF));
		db.storeNature(Nature(NatureID(0x0D), Name("RELAXED"), 	EPrimaryStat::DEF,   	EPrimaryStat::SPEED));

		//+SPATK natures
		db.storeNature(Nature(NatureID(0x0E), Name("MODEST"), 	EPrimaryStat::SPATK, 	EPrimaryStat::ATK));
		db.storeNature(Nature(NatureID(0x0F), Name("MILD"), 	EPrimaryStat::SPATK, 	EPrimaryStat::DEF));
		db.storeNature(Nature(NatureID(0x10), Name("RASH"), 	EPrimaryStat::SPATK, 	EPrimaryStat::SPDEF));
		db.storeNature(Nature(NatureID(0x11), Name("QUIET"), 	EPrimaryStat::SPATK, 	EPrimaryStat::SPEED));

		//+SPDEF natures
		db.storeNature(Nature(NatureID(0x12), Name("CALM"), 	EPrimaryStat::SPDEF, 	EPrimaryStat::ATK));
		db.storeNature(Nature(NatureID(0x13), Name("GENTLE"), 	EPrimaryStat::SPDEF, 	EPrimaryStat::DEF));
		db.storeNature(Nature(NatureID(0x14), Name("CAREFUL"), 	EPrimaryStat::SPDEF, 	EPrimaryStat::SPATK));
		db.storeNature(Nature(NatureID(0x15), Name("SASSY"), 	EPrimaryStat::SPDEF, 	EPrimaryStat::SPEED));

		//+SPEED natures
		db.storeNature(Nature(NatureID(0x16), Name("TIMID"), 	EPrimaryStat::SPEED, 	EPrimaryStat::ATK));
		db.storeNature(Nature(NatureID(0x17), Name("HASTY"), 	EPrimaryStat::SPEED, 	EPrimaryStat::DEF));
		db.storeNature(Nature(NatureID(0x18), Name("JOLLY"), 	EPrimaryStat::SPEED, 	EPrimaryStat::SPATK));
		db.storeNature(Nature(NatureID(0x19), Name("NAIVE"), 	EPrimaryStat::SPEED, 	EPrimaryStat::SPDEF));
	}

	/*****************************************************************
	 *****************************************************************/

	void TestGame::onSetup(void)
	{
		createNatures();

		Database &db = getDatabase();
		ScriptInterface &scriptIF = getScriptInterface();

		//Create abilities
		db.storeAbility(Ability(0x001, "DOWNLOAD",   	"Lowers the opposing Pokémon's Attack stat.", 			scriptIF));
		db.storeAbility(Ability(0x002, "INTIMIDATE", 	"Adjusts power based on an opposing Pokémon's stats.", 	scriptIF));
		//db.storeAbility(Ability(0x003, "DRIZZLE", 		"The Pokémon makes it rain when it enters a battle.", 	scriptIF));

		char mfxfile[48];
		for(MoveEffectID mfxid = 0x001; mfxid <= 0xFFF; mfxid++)
		{
			sprintf(mfxfile, "data/scripts/mfx/0x%03x.as", mfxid);
			if(fileExists(mfxfile))
			{
				db.storeMoveEffect(MoveEffect(mfxid, scriptIF));
			}
		}

		//Create test moves
		db.storeMove(PKMN::Move(MoveID(0x001), Name("TACKLE"), EType::NORMAL, EMoveContact::PHYSICAL,
					 MovePP(35), MoveBasePower(35), Percentage(95), MovePriority(0),
					 MoveEffectID(0x000), Percentage(0), EMoveTarget::SINGLE_OPPONENT,
					 MoveFlagList({0,1,2,3}), DescriptionText("A normal tackling attack.")));

		db.storeMove(PKMN::Move(MoveID(0x002), Name("STRINGSHOT"), EType::BUG, EMoveContact::STATUS,
					 MovePP(35), MoveBasePower(0), Percentage(100), MovePriority(0),
					 MoveEffectID(0x044), Percentage(100), EMoveTarget::SINGLE_OPPONENT,
					 MoveFlagList({0,1,2,3}), DescriptionText("Shoot a string at the opponent to reduce his speed.")));

		db.storeMove(PKMN::Move(MoveID(0x003), Name("ABSORB"), EType::GRASS, EMoveContact::SPECIAL,
					 MovePP(35), MoveBasePower(20), Percentage(100), MovePriority(0),
					 MoveEffectID(0x0DD), Percentage(100), EMoveTarget::SINGLE_OPPONENT,
					 MoveFlagList({0,1,2,3}), DescriptionText("Drain HP from the enemy.")));

		//Load species from file
		cout << "Loaded " << db.loadSpeciesFromFile("data/species.txt") << " species from file." << endl;
		getSpritebank().loadTexture("test", "res/img/test.png");

		Party parties[2];
		parties[0].addMember(Pokemon(db, SpeciesID(0x001), Level(1)));
		parties[0].addMember(Pokemon(db, SpeciesID(0x001), Level(1)));
		parties[0].addMember(Pokemon(db, SpeciesID(0x001), Level(1)));
		parties[0].addMember(Pokemon(db, SpeciesID(0x001), Level(1)));
		parties[0].addMember(Pokemon(db, SpeciesID(0x001), Level(1)));
		parties[0].addMember(Pokemon(db, SpeciesID(0x001), Level(1)));
		parties[1].addMember(Pokemon(db, SpeciesID(0x001), Level(1))); //Enemy team contains only 1 pokemon (wild battle)

		Moveset moveset;
		moveset[0] = MoveID(0x003);
		parties[0][0].setMoveset(moveset);

		//Start battle
		setBattle(new Battle(*this, new DefaultBattleMechanics(*this), EBattleType::SINGLE_WILD, parties[0], parties[1]));
	}

	/*****************************************************************
	 *****************************************************************/

	void TestGame::onUpdate(float dt)
	{
		//Update battle
		if(getBattle() != nullptr)
		{
			getBattle()->update(getKeyboard(), getMouse(), dt);
		}

		//Close when escape was pressed
		if (getKeyboard().isKeyPressed(Keyboard::Escape))
		{
			getWindow().close();
		}
	}

	/*****************************************************************
	 *****************************************************************/

	void TestGame::onRender(void)
	{
		//Render battle
		if(getBattle() != nullptr)
		{
			getBattle()->render(getWindow());
		}
	}
}
