/*****************************************************************
 **' InitBattleScene.cpp
 *****************************************************************
 **' Created on: 25.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "InitBattleScene.h"
#include "Battle.h"
#include "IGame.h"

namespace PKMN
{
	InitBattleScene::InitBattleScene(Battle &battle)
		:IBattleScene(battle), m_elapsedTime(0.0f)
	{
		cout << "Battle started" << endl;

		float padding = 64, spritesz = 180;
		const Vector2u &windowsz = battle.getParentGame().getWindow().getSize();
		Spritebank &sprbk = getParentBattle().getParentGame().getSpritebank();
		sprbk.createSprite("InitBattleScene::PlayerPokemon", "test").setPosition(padding, windowsz.y - padding - spritesz);
		sprbk.createSprite("InitBattleScene::EnemyPokemon",  "test").setPosition(windowsz.x - padding - spritesz, padding);
	}

	/*****************************************************************
	 *****************************************************************/

	void InitBattleScene::update(const Keyboard &kb, const Mouse &mouse, float dt)
	{
		switch(getParentBattle().getBattleType())
		{
			case EBattleType::SINGLE_WILD:
			{
				if(kb.isKeyPressed(Keyboard::Space))
				{
					//Extract neccessary values
					Battle &battle = getParentBattle();
					IGame &game = battle.getParentGame();
					const Database &db = game.getDatabase();
					IBattleMechanics &mech = battle.getBattleMechanics();

					Pokemon &playerPkmn = battle.getActivePlayerPokemon();
					Pokemon &enemyPkmn = battle.getActiveEnemyPokemon();
					MoveID moveID = playerPkmn.getMoveset()[0];
					const Move &move = db.getMove(moveID);
					const MoveEffect &mfx = db.getMoveEffect(move.getEffectID());

					cout << playerPkmn.getNickname() << " used " << move.getName() << "." << endl;

					//Move hits
					if(mech.willMoveHit(moveID))
					{
						bool crit;
						if((crit = mech.willMoveHitCritically(moveID)) == true)
						{
							cout << "It's a critical hit!" << endl;
						}

						uint16_t dmg = mech.determineMoveDamage(moveID, crit);
						cout << "Dealing " << dmg << " damage." << endl;

						//Invoke onHit handler
						mfx.onHit(playerPkmn, enemyPkmn, moveID, dmg, crit);
					}

					//Move misses
					else
					{
						cout << playerPkmn.getNickname() << " missed." << endl;

						//Calculate damage that would've been done
						uint16_t dmg = mech.determineMoveDamage(moveID, false);

						//Invoke onMiss handler
						mfx.onMiss(playerPkmn, enemyPkmn, moveID, dmg);
					}

					cout << endl;
				}
				else if(kb.isKeyPressed(Keyboard::Return))
				{
					terminate();
				}
			}
			break;

			default: cout << "Battle type not yet implemented!" << endl; break;
		}

		m_elapsedTime += dt;
	}

	/*****************************************************************
	 *****************************************************************/

	void InitBattleScene::render(sf::RenderWindow &window)
	{
		Spritebank &sprbk = getParentBattle().getParentGame().getSpritebank();
		window.draw(sprbk.getSprite("InitBattleScene::PlayerPokemon"));
		window.draw(sprbk.getSprite("InitBattleScene::EnemyPokemon"));
	}

	/*****************************************************************
	 *****************************************************************/

	InitBattleScene::~InitBattleScene(void)
	{
		Spritebank &sprbk = getParentBattle().getParentGame().getSpritebank();
		sprbk.destroySprite("InitBattleScene::PlayerPokemon");
		sprbk.destroySprite("InitBattleScene::EnemyPokemon");
	}
}
