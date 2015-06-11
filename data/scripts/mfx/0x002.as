//Move effect: 0x002
//Struggle

void onHit(Pokemon &caster, Pokemon &target, MoveID moveID, uint16 dmg, bool crit)
{
	uint16 maxHP = caster.getMaxStat(HP);
	uint16 currentHP = maxHP - uint16(caster.getStatStage(HP));
	
	print(caster.getNickname() + " is struggling.\n");
	
	//Move kills the user
	if(currentHP - maxHP / 4 < 0)
	{
		//Set HP to 0
		caster.setStatStage(HP, maxHP);
	}
	else
	{
		//Inflict Max HP / 4 damage to the user
		currentHP -= maxHP / 4;
		caster.setStatStage(HP, maxHP - currentHP);
	}
}