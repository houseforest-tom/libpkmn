/*****************************************************************
 **' EBattleScene.h
 *****************************************************************
 **' Created on: 25.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef EBATTLESCENE_H_
#define EBATTLESCENE_H_

namespace PKMN
{
	/**
	 * Possible battle scenes.
	 */
	enum class EBattleScene : uint8_t
	{
		INIT,			//Battle initialization scene
		MENU_MAIN,		//Main menu: select [FIGHT, TEAM, BAG, RUN]
		MENU_FIGHT,		//Player selected FIGHT
		MENU_TEAM,		//Player selected TEAM
		MENU_BAG,		//Player selected BAG
		TURN_BEGIN,		//The beginning of a new turn
		TURN_CORE,		//The core of the current turn
		TURN_END,		//The end of the current turn
		RUN				//The player tried to run
	};
}

#endif // EBATTLESCENE_H_
