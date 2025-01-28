// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstances/CoreGameInstance.h"

UCoreGameInstance::UCoreGameInstance()
{
	AllyCluster = NewObject<UCluster>();
	EnemyCluster = NewObject<UCluster>();
	Spawner = NewObject<UGridSpawner>();
}

void UCoreGameInstance::SpawnGrid(UWorld* InWorld, const FGrid& InGrid)
{
	if (Spawner)
	{
		Spawner->SpawnGrid(InWorld, InGrid);
	}

	AllyCluster->InitCluster(InWorld);
	EnemyCluster->InitCluster(InWorld);

	AllyCluster->SetTargetCluster(EnemyCluster);
	EnemyCluster->SetTargetCluster(AllyCluster);
}

void UCoreGameInstance::AddUnitToCluster(ABaseCharacter* InCharacter, ERoleType Type, bool IsAlly)
{
	if (IsAlly)
	{
		AllyCluster->AddUnit(InCharacter, Type);
	}
	else
	{
		EnemyCluster->AddUnit(InCharacter, Type);
	}
}

void UCoreGameInstance::SetPlayer(ABaseCharacter* InPlayer)
{
	Player = InPlayer;
	Player->SetMaxHealth(50);
	Player->SetCurrentHealth(50);

	AllyCluster->AddUnit(Player, ERoleType::Healer);
}

