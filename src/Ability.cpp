/*****************************************************************
 **' PokemonAbility.cpp
 *****************************************************************
 **' Created on: 16.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include <Ability.h>
#include <ScriptInterface.h>
#include <Pokemon.h>

namespace PKMN
{
	Ability::Ability(AbilityID id, const Name &name, const DescriptionText &desc, ScriptInterface &scriptIF)
		:m_scriptIF(scriptIF)
	{
		//Verify input parameters
		assert(id > 0);
		assert(name.length() > 0);
		assert(desc.length() > 0);

		m_ID = id;
		m_name.assign(name);
		m_description.assign(desc);

		char file[64], moduleName[64];
		sprintf(file, "data/scripts/afx/0x%03x.as", id);
		sprintf(moduleName, "afx:0x%03x", id);
		m_scriptModuleID = scriptIF.createModuleFromFile(Name(moduleName), Filename(file));
		m_scriptContextID = scriptIF.createContext();
	}

	/*****************************************************************
	 *****************************************************************/

	void Ability::print(void) const
	{
		cout << "<Pokemon Ability>" << endl;
		cout << "ID:\t\t\t" << m_ID << endl;
		cout << "Name:\t\t\t" << m_name << endl;
		cout << "Description:\t\t" << m_description << endl;
		cout << "</Pokemon Ability>" << endl << endl;
	}

	/*****************************************************************
	 * SCRIPT CALLBACKS
	 *****************************************************************/

	void Ability::onSwitchedIn(Pokemon &self, Pokemon &other) const
	{
		string funcdecl = "void onSwitchedIn(Pokemon&, Pokemon&)";
		if(m_scriptIF.existsScriptFunction(m_scriptModuleID, funcdecl))
		{
			m_scriptIF.prepareScriptFunction(m_scriptContextID, m_scriptModuleID, funcdecl);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 0, &self);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 1, &other);
			m_scriptIF.executeScriptFunction(m_scriptContextID);
		}
		else
		{
			//No behaviour defined
			//cout << funcdecl << " not implemented in ability module: " << m_scriptIF.getModule(m_scriptModuleID).GetName() << endl;
			NOOP;
		}
	}

	void Ability::onSwitchedOut(Pokemon &self, Pokemon &other) const
	{
		string funcdecl = "void onSwitchedOut(Pokemon&, Pokemon&)";
		if(m_scriptIF.existsScriptFunction(m_scriptModuleID, funcdecl))
		{
			m_scriptIF.prepareScriptFunction(m_scriptContextID, m_scriptModuleID, funcdecl);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 0, &self);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 1, &other);
			m_scriptIF.executeScriptFunction(m_scriptContextID);
		}
		else
		{
			//No behaviour defined
			//cout << funcdecl << " not implemented in ability module: " << m_scriptIF.getModule(m_scriptModuleID).GetName() << endl;
			NOOP;
		}
	}

	void Ability::onHitOpponent(Pokemon &self, Pokemon &other, MoveID move, uint16_t dmg, bool crit) const
	{
		string funcdecl = "void onHitOpponent(Pokemon&, Pokemon&, MoveID, uint16, bool)";
		if(m_scriptIF.existsScriptFunction(m_scriptModuleID, funcdecl))
		{
			m_scriptIF.prepareScriptFunction(m_scriptContextID, m_scriptModuleID, funcdecl);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 0, &self);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 1, &other);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 2, move);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 3, dmg);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 4, crit);
			m_scriptIF.executeScriptFunction(m_scriptContextID);
		}
		else
		{
			//No behaviour defined
			//cout << funcdecl << " not implemented in ability module: " << m_scriptIF.getModule(m_scriptModuleID).GetName() << endl;
			NOOP;
		}
	}

	void Ability::onHitAlly(Pokemon &self, Pokemon &other, MoveID move, uint16_t dmg, bool crit) const
	{
		string funcdecl = "void onHitAlly(Pokemon&, Pokemon&, MoveID, uint16, bool)";
		if(m_scriptIF.existsScriptFunction(m_scriptModuleID, funcdecl))
		{
			m_scriptIF.prepareScriptFunction(m_scriptContextID, m_scriptModuleID, funcdecl);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 0, &self);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 1, &other);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 2, move);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 3, dmg);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 4, crit);
			m_scriptIF.executeScriptFunction(m_scriptContextID);
		}
		else
		{
			//No behaviour defined
			//cout << funcdecl << " not implemented in ability module: " << m_scriptIF.getModule(m_scriptModuleID).GetName() << endl;
			NOOP;
		}
	}

	void Ability::onHitByOpponent(Pokemon &self, Pokemon &other, MoveID move, uint16_t dmg, bool crit) const
	{
		string funcdecl = "void onHitByOpponent(Pokemon&, Pokemon&, MoveID, uint16, bool)";
		if(m_scriptIF.existsScriptFunction(m_scriptModuleID, funcdecl))
		{
			m_scriptIF.prepareScriptFunction(m_scriptContextID, m_scriptModuleID, funcdecl);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 0, &self);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 1, &other);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 2, move);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 3, dmg);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 4, crit);
			m_scriptIF.executeScriptFunction(m_scriptContextID);
		}
		else
		{
			//No behaviour defined
			//cout << funcdecl << " not implemented in ability module: " << m_scriptIF.getModule(m_scriptModuleID).GetName() << endl;
			NOOP;
		}
	}

	void Ability::onHitByAlly(Pokemon &self, Pokemon &other, MoveID move, uint16_t dmg, bool crit) const
	{
		string funcdecl = "void onHitByAlly(Pokemon&, Pokemon&, MoveID, uint16, bool)";
		if(m_scriptIF.existsScriptFunction(m_scriptModuleID, funcdecl))
		{
			m_scriptIF.prepareScriptFunction(m_scriptContextID, m_scriptModuleID, funcdecl);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 0, &self);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 1, &other);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 2, move);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 3, dmg);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 4, crit);
			m_scriptIF.executeScriptFunction(m_scriptContextID);
		}
		else
		{
			//No behaviour defined
			//cout << funcdecl << " not implemented in ability module: " << m_scriptIF.getModule(m_scriptModuleID).GetName() << endl;
			NOOP;
		}
	}

	void Ability::onMajorStatusChanged(Pokemon &self, Pokemon &other, EMajorStatusAilment status, bool suffers) const
	{
		string funcdecl = "void onMajorStatusChanged(Pokemon&, Pokemon&, EMajorStatusAilment, bool)";
		if(m_scriptIF.existsScriptFunction(m_scriptModuleID, funcdecl))
		{
			m_scriptIF.prepareScriptFunction(m_scriptContextID, m_scriptModuleID, funcdecl);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 0, &self);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 1, &other);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 2, status);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 3, suffers);
			m_scriptIF.executeScriptFunction(m_scriptContextID);
		}
		else
		{
			//No behaviour defined
			//cout << funcdecl << " not implemented in ability module: " << m_scriptIF.getModule(m_scriptModuleID).GetName() << endl;
			NOOP;
		}
	}

	void Ability::onMinorStatusChanged(Pokemon &self, Pokemon &other, EMinorStatusAilment status, bool suffers) const
	{
		string funcdecl = "void onMinorStatusChanged(Pokemon&, Pokemon&, EMinorStatusAilment, bool)";
		if(m_scriptIF.existsScriptFunction(m_scriptModuleID, funcdecl))
		{
			m_scriptIF.prepareScriptFunction(m_scriptContextID, m_scriptModuleID, funcdecl);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 0, &self);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 1, &other);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 2, status);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 3, suffers);
			m_scriptIF.executeScriptFunction(m_scriptContextID);
		}
		else
		{
			//No behaviour defined
			//cout << funcdecl << " not implemented in ability module: " << m_scriptIF.getModule(m_scriptModuleID).GetName() << endl;
			NOOP;
		}
	}

	uint16_t Ability::onDetermineMoveDamage(const Pokemon &self, const Pokemon &other, MoveID moveID, uint16_t initial, bool crit) const
	{
		string funcdecl = "uint16 onDetermineMoveDamage(Pokemon&, Pokemon&, MoveID, uint16, bool)";
		if(m_scriptIF.existsScriptFunction(m_scriptModuleID, funcdecl))
		{
			m_scriptIF.prepareScriptFunction(m_scriptContextID, m_scriptModuleID, funcdecl);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 0, &self);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 1, &other);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 2, moveID);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 3, initial);
			m_scriptIF.setScriptFunctionArg(m_scriptContextID, 4, crit);
			m_scriptIF.executeScriptFunction(m_scriptContextID);

			return m_scriptIF.getScriptFunctionResult<uint16_t>(m_scriptContextID);
		}
		else
		{
			//No behaviour defined
			//cout << funcdecl << " not implemented in ability module: " << m_scriptIF.getModule(m_scriptModuleID).GetName() << endl;
			return initial;
		}
	}
}
