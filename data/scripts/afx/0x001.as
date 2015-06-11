//Ability effect: 1
//Lowers the opponents attack when switched in.

void onSwitchedIn(Pokemon &self, Pokemon &opponent)
{
	const Species @species = database.getSpecies(opponent.getSpeciesID());
	if(species.getBaseStat(DEF) >= species.getBaseStat(SPDEF))
	{
		//Opponent's base DEF > SPDEF -> raise SPATK
		self.setStatStage(SPATK, self.getStatStage(SPATK) + 1);
		print(self.getNickname() + "'s " + database.getAbility(0x001).getName() + " raised its SPATK.\n");
	}
	else
	{
		//Opponent's base DEF < SPDEF -> raise ATK
		self.setStatStage(ATK, self.getStatStage(ATK) + 1);
		print(self.getNickname() + "'s " + database.getAbility(0x001).getName() + " raised its ATK.\n");
	}
}