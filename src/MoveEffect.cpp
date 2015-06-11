/*****************************************************************
 **' MoveEffect.cpp
 *****************************************************************
 **' Created on: 17.05.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include <MoveEffect.h>
#include <ScriptInterface.h>
#include <Pokemon.h>

namespace PKMN
{
	MoveEffect::MoveEffect(MoveEffectID id, ScriptInterface &scriptIF)
		: m_ID(id), m_scriptIF(scriptIF)
	{
		//Move effect (ID: 0xABC) script located at 'data/scripts/mfx/0xABC.as'
		char file[48];
		sprintf(file, "data/scripts/mfx/0x%03x.as", id);

		//Name of corresponding script module is 'mfx:0xABC'
		char moduleName[24];
		sprintf(moduleName, "mfx:0x%03x", id);

		m_scriptModuleID = m_scriptIF.createModuleFromFile(Name(moduleName), Filename(file));
		m_scriptContextID = m_scriptIF.createContext();
	}

	/*****************************************************************
	 *****************************************************************/

	uint16_t MoveEffect::onDetermineMoveDamage(const Pokemon &caster, const Pokemon &target, MoveID moveID, uint16_t initial, bool crit) const
	{
		string funcdecl = "uint16 onDetermineMoveDamage(const Pokemon&, const Pokemon&, MoveID, uint16, bool)";
		if(m_scriptIF.existsScriptFunction(m_scriptModuleID, funcdecl))
		{
			m_scriptIF.prepareScriptFunction(
					m_scriptContextID,
					m_scriptModuleID,
					funcdecl
			);

			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 0, &caster);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 1, &target);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 2, moveID);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 3, initial);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 4, crit);
			m_scriptIF.executeScriptFunction(m_scriptContextID);

			//Return the new damage value
			return m_scriptIF.getScriptFunctionResult<uint16_t>(m_scriptContextID);
		}
		else
		{
			//No damage altering behaviour defined
			//cout << funcdecl << " not implemented in move effect module: " << m_scriptIF.getModule(m_scriptModuleID).GetName() << endl;
			return initial;
		}
	}

	/*****************************************************************
	 *****************************************************************/

	void MoveEffect::onHit(Pokemon &caster, Pokemon &target, MoveID moveID, uint16_t dmg, bool crit) const
	{
		string funcdecl = "void onHit(Pokemon&, Pokemon&, MoveID, uint16, bool)";
		if(m_scriptIF.existsScriptFunction(m_scriptModuleID, funcdecl))
		{
			m_scriptIF.prepareScriptFunction(
					m_scriptContextID,
					m_scriptModuleID,
					funcdecl
			);

			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 0, &caster);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 1, &target);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 2, moveID);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 3, dmg);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 4, crit);
			m_scriptIF.executeScriptFunction(m_scriptContextID);
		}

		//No behaviour defined
		else
		{
			//cout << funcdecl << " not implemented in move effect module: " << m_scriptIF.getModule(m_scriptModuleID).GetName() << endl;
			NOOP;
		}
	}

	/*****************************************************************
	 *****************************************************************/

	void MoveEffect::onMiss(Pokemon &caster, Pokemon &target, MoveID moveID, uint16_t dmg) const
	{
		string funcdecl = "void onMiss(Pokemon&, Pokemon&, MoveID, uint16)";
		if(m_scriptIF.existsScriptFunction(m_scriptModuleID, funcdecl))
		{
			m_scriptIF.prepareScriptFunction(
					m_scriptContextID,
					m_scriptModuleID,
					funcdecl
			);

			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 0, &caster);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 1, &target);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 2, moveID);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 3, dmg);
			m_scriptIF.executeScriptFunction(m_scriptContextID);
		}

		//No behaviour defined
		else
		{
			//cout << funcdecl << " not implemented in move effect module: " << m_scriptIF.getModule(m_scriptModuleID).GetName() << endl;
			NOOP;
		}
	}
}
