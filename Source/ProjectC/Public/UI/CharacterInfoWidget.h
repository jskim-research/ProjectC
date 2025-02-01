// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "CharacterInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API UCharacterInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetName(const FString& InName);
	void SetHPRatio(float InRatio);
	
protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* Name;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UProgressBar* HPBar;
};
