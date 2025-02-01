// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerHealerCharacter.h"

APlayerHealerCharacter::APlayerHealerCharacter()
{
    static ConstructorHelpers::FClassFinder<AActor> AllyProjectileClassFinder(TEXT("/Game/Blueprints/Projectiles/BP_AllyProjectile"));
    static ConstructorHelpers::FClassFinder<AActor> EnemyProjectileClassFinder(TEXT("/Game/Blueprints/Projectiles/BP_EnemyProjectile"));

    if (AllyProjectileClassFinder.Succeeded())
    {
        AllyProjectileBlueprint = AllyProjectileClassFinder.Class;
    }

    if (EnemyProjectileClassFinder.Succeeded())
    {
        EnemyProjectileBlueprint = EnemyProjectileClassFinder.Class;
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

    if (IsAlly)
    {
        GetWorld()->SpawnActor(AllyProjectileBlueprint, &Location, &Rotation, SpawnParams);
    }
    else
    {
        GetWorld()->SpawnActor(EnemyProjectileBlueprint, &Location, &Rotation, SpawnParams);
    }
}
