// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Characters/BaseCharacter.h"
#include "BlackboardCharacterArrayObject.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTC_API UBlackboardCharacterArrayObject : public UObject
{
	GENERATED_BODY()
	
public:
	void AddCharacter(ABaseCharacter* InCharacter);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ABaseCharacter*> CharacterArray;

};
