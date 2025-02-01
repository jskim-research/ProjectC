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

void ABaseCharacter::SetBaseColor(FLinearColor& Color)
{
	USkeletalMeshComponent* SelfMesh = GetMesh();

	if (!SelfMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABaseCharacter::SetBaseColor: Mesh is not found."));
		return;
	}

	// 메쉬에 적용된 기본 머티리얼을 기반으로 동적 인스턴스를 생성
	UMaterialInstanceDynamic* DynamicMaterial = SelfMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (!DynamicMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABaseCharacter::SetBaseColor: DynamicMaterial is not working."));
		return;
	}

	DynamicMaterial->SetVectorParameterValue(FName("TeamColor"), Color);
}

void ABaseCharacter::SetIsAlly(bool InIsAlly)
{
	IsAlly = InIsAlly;
}

bool ABaseCharacter::GetIsAlly() const
{
	return IsAlly;
}
