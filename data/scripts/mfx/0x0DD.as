//Move effect: 0x0DD.
//Absorbs half of the damage done to the opponent.

void onHit(Pokemon &caster, Pokemon &target, MoveID moveID, uint16 dmg, bool crit)
{
	//Calculate amount of HP to absorb from opponent
	//In this case 50% of inflicted damage
	uint16 absorbedAmount = dmg / 2;
	
	//More HP absorbed than lost before
	if(absorbedAmount > uint16(caster.getStatStage(HP))){ absorbedAmount = uint16(caster.getStatStage(HP)); }
	
	//Print message
	print(caster.getNickname() + " stole " + absorbedAmount + " HP from opposing " + target.getNickname() + ".\n");
	
	//Add absorbed HP to current HP
	caster.setStatStage(HP, StatStage(caster.getStatStage(HP) - absorbedAmount));
}