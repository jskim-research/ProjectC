// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "PlayerTankCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API APlayerTankCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:
	APlayerTankCharacter();
	virtual void BeginPlay() override;
	virtual void Act() override;

private:
};
