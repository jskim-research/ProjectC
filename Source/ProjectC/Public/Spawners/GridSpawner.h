// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Grid.h"
#include "Enums/RoleType.h"
#include "UObject/NoExportTypes.h"
#include "Characters/BaseCharacter.h"
#include "GridSpawner.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API UGridSpawner : public UObject
{
	GENERATED_BODY()
	
public:
	UGridSpawner();

	// Grid 전체 타일 순회하며 캐릭터 스폰
	void SpawnGrid(UWorld* InWorld, const FGrid& InGrid);

	// 실제 캐릭터 스폰하는 함수 
	void Spawn(UWorld* InWorld, FVector Position, const FGridTile& TileInfo);

private:
	TSubclassOf<ABaseCharacter> TankBlueprint;
	TSubclassOf<ABaseCharacter> DealerBlueprint;
	TSubclassOf<ABaseCharacter> HealerBlueprint;
};
