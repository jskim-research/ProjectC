// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class PROJECTC_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Action 함수들
	virtual void Act();
	virtual void Hit();
	virtual void Die();

	virtual void SetMaxHealth(float InMaxHealth);
	float GetMaxHealth() const;

	virtual void SetCurrentHealth(float InCurrentHealth);
	float GetCurrentHealth() const;

	void SetRange(float InRange);
	float GetRange() const;

	void SetBaseColor(FLinearColor& Color);

	virtual void SetIsAlly(bool InIsAlly);

	UFUNCTION(BlueprintPure)
	bool GetIsAlly() const;

	virtual void SetUIVisibility(bool InVisibility);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float MaxHealth = 0;
	float CurrentHealth = 0;

	// 사정거리
	float Range = 0;

	bool IsAlly = false;
};
