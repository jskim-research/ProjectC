// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NPCCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "NPCTankCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API ANPCTankCharacter : public ANPCCharacter
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetIsAlly(bool InIsAlly) override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Shield;
};
