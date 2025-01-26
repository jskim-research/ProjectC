// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NPCCharacter.h"
#include "NPCHealerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API ANPCHealerCharacter : public ANPCCharacter
{
	GENERATED_BODY()
	
public:
	ANPCHealerCharacter();
	virtual void Act() override;

private:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AActor> ProjectileBlueprint;
};
