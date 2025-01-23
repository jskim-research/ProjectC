// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PlayerCharacter.h"
#include "PlayerDealerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API APlayerDealerCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:
	APlayerDealerCharacter();
	virtual void BeginPlay() override;
	virtual void Act() override;

private:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AActor> ProjectileBlueprint;

};
