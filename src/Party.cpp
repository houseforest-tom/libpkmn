/*****************************************************************
 **' PokemonTeam.cpp
 *****************************************************************
 **' Created on: 23.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include <Party.h>
#include <memory.h>

namespace PKMN
{
	Party::Party(void)
	{
		m_members.reserve(MAX_TEAM_SIZE);
	}

	/*****************************************************************
	 *****************************************************************/

	Party::Party(const vector<Pokemon> &members)
	{
		//Assert valid team size
		unsigned sz = members.size();
		assert(sz < MAX_TEAM_SIZE);
		m_members.reserve(MAX_TEAM_SIZE);

		//Copy members from vector
		for (unsigned slot = 0; slot < sz; slot++)
		{
			m_members.push_back(members[slot]);
		}

	}

	/*****************************************************************
	 *****************************************************************/

	bool Party::overwriteMember(unsigned slot, const Pokemon &member)
	{
		//Out of range
		if (slot >= m_members.size()) return false;

		//Construct new team
		vector<Pokemon> updated;
		updated.reserve(MAX_TEAM_SIZE);
		for (unsigned i = 0; i < m_members.size(); i++)
		{
			if (i == slot)
			updated.push_back(member);
			else
			updated.push_back(m_members[i]);
		}

		//Replace internal team by new one
		m_members.clear();
		for (unsigned i = 0; i < updated.size(); i++)
		{
			m_members.push_back(updated[i]);
		}

		return true;
	}

	/*****************************************************************
	 *****************************************************************/

	bool Party::addMember(const Pokemon &member)
	{
		//Team full already
		if (m_members.size() >= MAX_TEAM_SIZE) return false;

		//Add new member
		m_members.push_back(member);

		return true;
	}

	/*****************************************************************
	 *****************************************************************/

	bool Party::removeMember(unsigned slot)
	{
		//Out of range
		if (slot >= m_members.size()) return false;

		//Construct new team
		vector<Pokemon> updated;
		updated.reserve(MAX_TEAM_SIZE);
		for (unsigned i = 0; i < m_members.size(); i++)
		{
			//Omit member to remove
			if (i != slot)
				updated.push_back(m_members[i]);
		}

		//Replace internal team by new one
		m_members.clear();
		for (unsigned i = 0; i < updated.size(); i++)
		{
			m_members.push_back(updated[i]);
		}

		return true;
	}

	/*****************************************************************
	 *****************************************************************/

	void Party::clear(void)
	{
		//Reset team
		m_members.clear();
	}

	/*****************************************************************
	 *****************************************************************/

	void Party::print(void) const
	{
		cout << "<Party>" << endl;

		cout << "Size:\t\t\t" << getSize() << endl;
		cout << "Members:" << endl;

		for (unsigned slot = 0; slot < getSize(); slot++)
		{
			m_members[slot].print();
		}

		cout << "</Party>" << endl << endl;
	}
}
