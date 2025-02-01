// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PlayerCharacter.h"
#include "PlayerHealerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API APlayerHealerCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:
	APlayerHealerCharacter();
	virtual void BeginPlay() override;
	virtual void Act() override;

private:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AActor> AllyProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AActor> EnemyProjectileBlueprint;

};
