// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"

UStatComponent::UStatComponent()
{
	/*
	FStat cHP;
	cHP.name = "currentHP";
	table.Add(cHP);

	FStat mHP;
	mHP.name = "maxHP";
	table.Add(mHP);

	FStat cAP;
	cAP.name = "currentAP";
	table.Add(cAP);

	FStat mAP;
	mAP.name = "maxAP";
	table.Add(mAP);

	FStat cSP;
	cSP.name = "currentSP";
	table.Add(cSP);

	FStat mSP;
	mSP.name = "maxSP";
	table.Add(mSP);

	FStat cG;
	cG.name = "currentGauge";
	table.Add(cG);

	FStat mG;
	mG.name = "maxGauge";
	table.Add(mG);

	FStat str;
	str.name = "Strength";
	table.Add(str);

	FStat mag;
	mag.name = "Magic";
	table.Add(mag);

	FStat def;
	def.name = "Defense";
	table.Add(def);

	FStat res;
	res.name = "Resilience";
	table.Add(res);

	FStat agi;
	agi.name = "Agility";
	table.Add(agi);

	FStat move;
	move.name = "Movement";
	table.Add(move);

	FStat luck;
	luck.name = "Luck";
	table.Add(luck);
	*/

	table.Add(FStat(TEXT("currentHP")));	//current health points
	table.Add(FStat(TEXT("maxHP")));		//max health points
	table.Add(FStat(TEXT("currentSP")));	//
	table.Add(FStat(TEXT("maxSP")));		//
	table.Add(FStat(TEXT("currentAP")));	//current action points
	table.Add(FStat(TEXT("maxAP")));		//max action points
	table.Add(FStat(TEXT("currentGauge")));	//current special gauge
	table.Add(FStat(TEXT("maxGauge")));		//max special gauge

	table.Add(FStat(TEXT("Strength")));		//strength determines damage of physical attacks
	table.Add(FStat(TEXT("Magic")));		//magic determines damage of magical attacks
	table.Add(FStat(TEXT("Defense")));		//defense determines physical damage reduction
	table.Add(FStat(TEXT("Resilience")));	//resilience determines magical damage reduction
	table.Add(FStat(TEXT("Agility")));		//agility determines turn order, (maximum movement = can be its own variable if needed)
	table.Add(FStat(TEXT("Luck")));			//determines success chances, critical chances, etc
	

}

void UStatComponent::AddTable(UStatComponent& ActorTable)
{
	for (int i = 0; i < table.Num(); i++)
	{
		table[i].value += ActorTable.GetStatTable()[i].value;
	}
}

void UStatComponent::RemoveTable(UStatComponent& ActorTable)
{
	for (int i = 0; i < table.Num(); i++)
	{
		table[i].value -= ActorTable.GetStatTable()[i].value;
	}
}

int UStatComponent::GetStat(FString statName)
{
	for (FStat stat : table)
	{
		if (stat.name == statName)
		{
			return stat.value;
		}
	}
	return 0;
}

void UStatComponent::SetStat(FString statName, int amount)
{
	
	for (FStat& stat : table)
	{
		if (stat.name == statName)
		{
			stat.value = amount;
			stat.name = statName;
			break;
		}
	}
	/*
	for (int i = 0; i < table.Num(); i++)
	{
		if (table[i].name == statName)
		{
			table[i].value = amount;
			table[i].name = statName;
			break;
		}
	}
	*/
}
