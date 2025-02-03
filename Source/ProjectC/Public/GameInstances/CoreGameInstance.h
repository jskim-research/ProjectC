// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AI/ClusterController.h"
#include "Spawners/GridSpawner.h"
#include "Data/Grid.h"
#include "Data/Cluster.h"
#include "CoreGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API UCoreGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UCoreGameInstance();
	void SpawnGrid(UWorld* InWorld, const FGrid& InGrid);
	void AddUnitToCluster(ABaseCharacter* InCharacter, ERoleType Type, bool IsAlly);
	void SetPlayer(ABaseCharacter* InPlayer);
	void PerformPlayerCommand(EClusterCommand InClusterCommand);

private:	
	UPROPERTY()
	UCluster* AllyCluster;

	UPROPERTY()
	UCluster* EnemyCluster;

	UPROPERTY()
	UGridSpawner* Spawner;

	UPROPERTY()
	ABaseCharacter* Player;
};
