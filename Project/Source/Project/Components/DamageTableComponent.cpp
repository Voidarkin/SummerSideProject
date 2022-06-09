// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTableComponent.h"

UDamageTableComponent::UDamageTableComponent()
{
	//Physical
	FType slash;
	slash.name = "Slash";
	table.Add(slash);

	FType pierce;
	pierce.name = "Pierce";
	table.Add(pierce);

	FType blud;
	blud.name = "Bludgeon";
	table.Add(blud);

	//Fractal
	FType lightning;
	lightning.name = "lightning";
	table.Add(lightning);

	FType earth;
	earth.name = "Earth";
	table.Add(earth);

	FType resonant;
	resonant.name = "Resonant";
	table.Add(resonant);

	//Natural
	FType fire;
	fire.name = "Fire";
	table.Add(fire);

	FType water;
	water.name = "Water";
	table.Add(water);

	FType plant;
	plant.name = "Plant";
	table.Add(plant);

	//Esoteric
	FType chaos;
	chaos.name = "Chaos";
	table.Add(chaos);

	FType control;
	control.name = "Control";
	table.Add(control);

	FType corrupt;
	corrupt.name = "Corruption";
	table.Add(corrupt);
}

void UDamageTableComponent::AddTable(UDamageTableComponent& ActorTable)
{
	for (int i = 0; i < table.Num(); i++)
	{
		ActorTable.GetDamageTable()[i].value += table[i].value;
	}
}

void UDamageTableComponent::RemoveTable(UDamageTableComponent& ActorTable)
{
	for (int i = 0; i < table.Num(); i++)
	{
		ActorTable.GetDamageTable()[i].value -= table[i].value;
	}
}

