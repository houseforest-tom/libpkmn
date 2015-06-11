//Ability effect: 2
//Lowers the opponents attack when switched in.

void onSwitchedIn(Pokemon &self, Pokemon &opponent)
{
	if(opponent.getStatStage(ATK) > -6)
	{
		opponent.setStatStage(ATK, opponent.getStatStage(ATK) - 1);
		print(self.getNickname() + "'s " + database.getAbility(0x002).getName() + " lowered opposing " + opponent.getNickname() + "'s ATK.\n");
	}
	else
	{
		print("Opposing " + opponent.getNickname() + "'s ATK cannot be lowered any further.\n");
	}
}