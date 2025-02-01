// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Components/WidgetComponent.h"
#include "UI/CharacterInfoWidget.h"
#include "NPCCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API ANPCCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	ANPCCharacter();
	virtual void SetMaxHealth(float InMaxHealth) override;
	virtual void SetCurrentHealth(float InCurrentHealth) override;
	virtual void SetUIVisibility(bool InVisibility) override;

protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere)
	UWidgetComponent* InfoWidgetComponent;

	UPROPERTY(VisibleAnywhere)
	UCharacterInfoWidget* InfoWidget;
};
