// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPCDealerCharacter.h"
#include "Components/BoxComponent.h"

ANPCDealerCharacter::ANPCDealerCharacter()
{
    // Projectile 이렇게 나누지 말고, shield 처럼 collision channel 바꾸는 형태로 가야함 
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

void ANPCDealerCharacter::Act()
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

void ANPCDealerCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    if (InfoWidget)
    {
        InfoWidget->SetName("Dealer");
    }
}
