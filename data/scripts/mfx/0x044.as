//Move effect: 0x044
//Lowers opponent's speed stat.

void onHit(Pokemon &caster, Pokemon &target, MoveID moveID, uint16 dmg, bool crit)
{	
	if(target.getStatStage(SPEED) > -6)
	{
		//Reduce SPEED by one stage
		target.setStatStage(SPEED, target.getStatStage(SPEED) - 1);
		print("Opposing " + target.getNickname() + "'s SPEED fell.\n");
	}
	else
	{
		print("Opposing " + target.getNickname() + "'s SPEED cannot be lowered any further.\n");
	}
}