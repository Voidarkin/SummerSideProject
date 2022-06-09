// Fill out your copyright notice in the Description page of Project Settings.


#include "ConditionTableComponent.h"

UConditionTableComponent::UConditionTableComponent()
{

	FConditionInfo poison;
	poison.name = "Poison";
	table.Add(poison);

	FConditionInfo rooted;
	rooted.name = "Rooted";
	table.Add(rooted);

	FConditionInfo stunned;
	stunned.name = "Stunned";
	table.Add(stunned);

}


void UConditionTableComponent::AddTable(UConditionTableComponent& ActorTable)
{
	for (int i = 0; i < table.Num(); i++)
	{
		ActorTable.GetConditionTable()[i].value += table[i].value;
	}
}

void UConditionTableComponent::RemoveTable(UConditionTableComponent& ActorTable)
{
	for (int i = 0; i < table.Num(); i++)
	{
		ActorTable.GetConditionTable()[i].value -= table[i].value;
	}
}

