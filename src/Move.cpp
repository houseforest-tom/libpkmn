/*****************************************************************
 **' PokemonMove.cpp
 *****************************************************************
 **' Created on: 16.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include <Move.h>

namespace PKMN
{
	Move::Move(MoveID id, const Name &name, EType type, EMoveContact contact, MovePP pp,
						 MoveBasePower pwr, Percentage acc, MovePriority prio, MoveEffectID effect,
						 Percentage effectChance, EMoveTarget target, const MoveFlagList &flags,
						 const DescriptionText &desc)
			: m_contact(contact), m_effectID(effect), m_target(target), m_flags(flags)
	{
		//Verify input parameters
		assert(id > 0);
		assert(name.length() > 0);
		assert(type != EType::NONE);
		assert(pp > 0);
		assert(pwr >= 0);
		assert(acc <= 100);
		assert(-6 <= prio && prio <= 6);
		assert(desc.length() > 0);
		assert(effectChance >= 0 && effectChance <= 100);

		m_ID = id;
		m_name.assign(name);
		m_type = type;
		m_pp = pp;
		m_basePower = pwr;
		m_accuracy = acc;
		m_priority = prio;
		m_effectChance = effectChance;
		m_description.assign(desc);
	}

	/*****************************************************************
	 *****************************************************************/

	void Move::print(void) const
	{
		cout << "<Pokemon Move>" << endl;
		cout << "ID:\t\t\t" << m_ID << endl;
		cout << "Name:\t\t\t" << m_name << endl;
		cout << "Type:\t\t\t" << ENUM_STRING(EType, m_type) << endl;
		cout << "Contact:\t\t" << ENUM_STRING(EMoveContact, m_contact) << endl;
		cout << "PP:\t\t\t" << (unsigned) m_pp << endl;
		cout << "Power:\t\t\t" << (unsigned) m_basePower << endl;
		cout << "Accuracy:\t\t" << (unsigned) m_accuracy << endl;
		cout << "Priority:\t\t" << (signed) m_priority << endl;
		cout << "Description:\t\t" << m_description << endl;
		cout << "</Pokemon Move>" << endl << endl;
	}
}
