// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NPCCharacter.h"
#include "NPCDealerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API ANPCDealerCharacter : public ANPCCharacter
{
	GENERATED_BODY()

public:
	ANPCDealerCharacter();
	virtual void Act() override;

private:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AActor> AllyProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AActor> EnemyProjectileBlueprint;
};
