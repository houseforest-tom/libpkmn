//Move effect: 0x005
//Poisons the opponent.

void onHit(Pokemon &caster, Pokemon &target, MoveID moveID, uint16 dmg, bool crit)
{
	if(target.getMajorStatusAilment() == EMajorStatusAilment::NONE)
	{
		target.setMajorStatusAilment(EMajorStatusAilment::POISON);
	}
	else
	{
		print("Could not poison " + target.getNickname() + ".\n");
	}
}