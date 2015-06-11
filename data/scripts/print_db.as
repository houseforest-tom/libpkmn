void main(void)
{
	print("Database contents:\n");
	
	print("Natures: (" + database.getNatureCount() + ")\n");
	for(NatureID id = 0x01; id <= database.getNatureCount(); id++)
	{
		const Nature @n = database.getNature(id);
		print("ID: " + id + "\tName: " + n.getName() + "\t");
		
		if(n.isNeutral())
		{
			print("Neutral");
		}
		else
		{
			print("+" + tostring(n.getIncreasedStat()) + "\t-" + tostring(n.getDecreasedStat()));
		}
		
		//Test calculation
		n.calcInfluencedStat(EPrimaryStat::ATK, 256);
		
		print("\n");
	}
	
	print("\nAbilities: (" + database.getAbilityCount() + ")\n");
	for(AbilityID id = 0x01; id <= database.getAbilityCount(); id++)
	{
		const Ability @a = database.getAbility(id);
		print("ID: " + id + "\tName: " + a.getName() + "\tDesc: " + a.getDescription() + "\n");
	}
	
	print("\nMoves: (" + database.getMoveCount() + ")\n");
	for(MoveID id = 0x01; id <= database.getMoveCount(); id++)
	{
		const Move @m = database.getMove(id);
		print("ID: " + id + "\tName: " + m.getName() + "\tDesc: " + m.getDescription() + "\tEffect ID: " + m.getEffectID() + "\n");
	}
	
	print("\nSpecies: (" + database.getSpeciesCount() + ")\n");
	for(SpeciesID id = 0x01; id <= database.getSpeciesCount(); id++)
	{
		const Species @s = database.getSpecies(id);
		print("ID: " + id + "\tName: " + s.getName() + "\tTyping: " + tostring(s.getType(0)) + " / " + tostring(s.getType(1)) + "\n");
	}
	
	print("\n");
}