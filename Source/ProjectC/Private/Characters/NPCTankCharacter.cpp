// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPCTankCharacter.h"

void ANPCTankCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Mesh 아래에 있는 Shield 찾기
    if (GetMesh())
    {
        Shield = Cast<UStaticMeshComponent>(GetMesh()->GetChildComponent(0)); // 첫 번째 자식이 Shield라고 가정
        if (!Shield)
        {
            UE_LOG(LogTemp, Warning, TEXT("Shield does not exist"));
        }
    }
}

void ANPCTankCharacter::SetIsAlly(bool InIsAlly)
{
    Super::SetIsAlly(InIsAlly);

    if (Shield)
    {
        if (InIsAlly)
        {
            // AllyShield로 Collision Object Type 설정
            Shield->SetCollisionObjectType(ECC_GameTraceChannel2);

            // EnemyProjectile과 Overlap 되도록 설정
            Shield->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);
        }
        else
        {
            // EnemyShield로 Collision Object Type 설정
            Shield->SetCollisionObjectType(ECC_GameTraceChannel4);

            // AllyProjectile과 Overlap 되도록 설정
            Shield->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
        }
    }
}
