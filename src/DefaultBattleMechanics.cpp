/*****************************************************************
 **' DefaultBattleMechanics.cpp
 *****************************************************************
 **' Created on: 24.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "DefaultBattleMechanics.h"
#include "Battle.h"
#include "IGame.h"

namespace PKMN
{
	DefaultBattleMechanics::DefaultBattleMechanics(IGame &game)
		:IBattleMechanics(game)
	{
		NOOP;
	}

	/*****************************************************************
	 *****************************************************************/

	ETurnOrder PKMN::DefaultBattleMechanics::determineTurnOrder(void)
	{
		//Get current speed stats of player and enemy pokemon
		StatValue playerSpeed = getParentGame().getBattle()->getActivePlayerPokemon().getCurrentStat(EPrimaryStat::SPEED);
		StatValue enemySpeed  = getParentGame().getBattle()->getActiveEnemyPokemon().getCurrentStat(EPrimaryStat::SPEED);

		//Player is faster
		if(playerSpeed > enemySpeed) return ETurnOrder::PLAYER_FIRST;

		//Enemy is faster
		if(enemySpeed > playerSpeed) return ETurnOrder::OPPONENT_FIRST;

		//Speed tie -> decide randomly
		return ((rand() % 2) == 0 ? ETurnOrder::PLAYER_FIRST : ETurnOrder::OPPONENT_FIRST);
	}

	/*****************************************************************
	 *****************************************************************/

	bool DefaultBattleMechanics::willMoveHit(MoveID moveID)
	{
		//Get last move used by either player or enemy
		const Move &move = getParentGame().getDatabase().getMove(moveID);
		Percentage moveAcc = move.getAccuracy();

		//Move always hits -> skip accuracy check
		if(moveAcc == 0 || moveAcc > 100) return true;

		//Get currently active pokemon
		const Pokemon &playerPokemon = getParentGame().getBattle()->getActivePlayerPokemon();
		const Pokemon &enemyPokemon  = getParentGame().getBattle()->getActiveEnemyPokemon();

		//Calculate chance that the move will hit
		double acc = playerPokemon.getCurrentStat(ESecondaryStat::ACCURACY) / 100.0;
		double eva = enemyPokemon.getCurrentStat(ESecondaryStat::EVASION)   / 100.0;
		Percentage chance = moveAcc * acc / eva; //chance to hit in percent

		//Move surely hits
		if(chance >= 100) return true;

		//Move hits this time
		if(rand() % 100 < chance) return true;

		//Move misses
		return false;
	}

	/*****************************************************************
	 *****************************************************************/

	bool DefaultBattleMechanics::willMoveHitCritically(MoveID move)
	{
		//For now, 1/16 chance to hit critically
		return ((rand() / (double)RAND_MAX) < (1.0 / 16.0));
	}

	/*****************************************************************
	 *****************************************************************/

	uint16_t DefaultBattleMechanics::determineMoveDamage(MoveID moveID, bool crit)
	{
		//Get information about move used
		const Move &move = getParentGame().getDatabase().getMove(moveID);
		MoveBasePower pwr = move.getBasePower();
		EMoveContact contact = move.getContact();

		//Status moves don't deal any damage
		if(contact == EMoveContact::STATUS) return 0;

		//Get player pokemon's offensive stat
		const Pokemon &playerPoke = getParentGame().getBattle()->getActivePlayerPokemon();
		Level level = playerPoke.getLevel();
		StatValue offensive;

		//Get enemy pokemon's defensive stat
		const Pokemon &enemyPoke = getParentGame().getBattle()->getActiveEnemyPokemon();
		StatValue defensive;

		//Ignore stat changes when critting
		if(!crit)
		{ 	//Normal hit
			offensive = playerPoke.getCurrentStat((contact == EMoveContact::PHYSICAL) ? EPrimaryStat::ATK : EPrimaryStat::SPATK);
			defensive = enemyPoke.getCurrentStat((contact == EMoveContact::PHYSICAL) ? EPrimaryStat::DEF : EPrimaryStat::SPDEF);
		}
		else
		{	//Crit
			offensive = playerPoke.getMaxStat((contact == EMoveContact::PHYSICAL) ? EPrimaryStat::ATK : EPrimaryStat::SPATK);
			defensive = enemyPoke.getMaxStat((contact == EMoveContact::PHYSICAL) ? EPrimaryStat::DEF : EPrimaryStat::SPDEF);
		}

		//Check for STAB
		double stab = 1.0;
		const Species &species = getParentGame().getDatabase().getSpecies(playerPoke.getSpeciesID());
		if(species.getType(0) == move.getType() || species.getType(1) == move.getType())
		{
			stab = 1.5;
		}

		//Calculate usually dealt damage
		uint16_t dmg = floor(floor(floor(2.0 * level / 5.0 + 2.0) * stab * (double)pwr * (double)offensive / (double)defensive) / 50.0) + 2.0;
		if(crit) dmg *= 2;

		/**
		 * Invoke possibly scripted effects
		 */

		//Move effect
		MoveEffectID mfxid = move.getEffectID();
		if(mfxid > 0)
		{
			const MoveEffect &movefx = getParentGame().getDatabase().getMoveEffect(mfxid);
			dmg = movefx.onDetermineMoveDamage(playerPoke, enemyPoke, moveID, dmg, crit);
		}

		//Ability
		AbilityID ablid = playerPoke.getAbilityID();
		if(ablid > 0)
		{
			const Ability &ability = getParentGame().getDatabase().getAbility(ablid);
			dmg = ability.onDetermineMoveDamage(playerPoke, enemyPoke, moveID, dmg, crit);
		}

		//TODO: Field effects

		//Return result
		return dmg;
	}

	/*****************************************************************
	 *****************************************************************/

	bool DefaultBattleMechanics::willBallCatch(unsigned ballID)
	{
		//TODO: implement
		return true;
	}

	/*****************************************************************
	 *****************************************************************/

	bool DefaultBattleMechanics::willRunSucceed(void)
	{
		//TODO: implement
		return true;
	}
}
