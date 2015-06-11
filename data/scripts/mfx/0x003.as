//Move effect: 0x003
//Puts the target to sleep.

void onHit(Pokemon &caster, Pokemon &target, MoveID moveID, uint16 dmg, bool crit)
{
	if(target.getMajorStatusAilment() == EMajorStatusAilment::NONE)
	{
		target.setMajorStatusAilment(SLEEP);
	}
	else
	{
		print("Could not put " + target.getNickname() + " to sleep.\n");
	}
}