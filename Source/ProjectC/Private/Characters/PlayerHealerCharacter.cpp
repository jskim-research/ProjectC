// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerHealerCharacter.h"

APlayerHealerCharacter::APlayerHealerCharacter()
{
    static ConstructorHelpers::FClassFinder<AActor> ProjectileClassFinder(TEXT("/Game/Blueprints/Projectiles/BP_Projectile"));
    if (ProjectileClassFinder.Succeeded())
    {
        ProjectileBlueprint = ProjectileClassFinder.Class;
    }
}

void APlayerHealerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void APlayerHealerCharacter::Act()
{
    FVector Location = GetActorLocation();
    FRotator Rotation = GetActorRotation();
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    SpawnParams.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;
    GetWorld()->SpawnActor(ProjectileBlueprint, &Location, &Rotation, SpawnParams);
}
