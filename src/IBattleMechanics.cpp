/*****************************************************************
 **' IBattleMechanics.cpp
 *****************************************************************
 **' Created on: 20.05.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include "IBattleMechanics.h"
#include "IGame.h"

PKMN::IGame &PKMN::IBattleMechanics::getParentGame(void)
{
	return m_parentGame;
}
