// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::Act()
{
}

void ABaseCharacter::Hit()
{
}

void ABaseCharacter::Die()
{
}

void ABaseCharacter::SetMaxHealth(float InMaxHealth)
{
	MaxHealth = InMaxHealth;
}

float ABaseCharacter::GetMaxHealth() const
{
	return MaxHealth;
}

void ABaseCharacter::SetCurrentHealth(float InCurrentHealth)
{
	CurrentHealth = InCurrentHealth;
}

float ABaseCharacter::GetCurrentHealth() const
{
	return CurrentHealth;
}

void ABaseCharacter::SetRange(float InRange)
{
	Range = InRange;
}

float ABaseCharacter::GetRange() const
{
	return Range;
}
