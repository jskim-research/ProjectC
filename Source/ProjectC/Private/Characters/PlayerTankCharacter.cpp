// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerTankCharacter.h"

APlayerTankCharacter::APlayerTankCharacter()
{
}

void APlayerTankCharacter::BeginPlay()
{
	Super::BeginPlay();

    // Mesh 아래에 있는 Shield 찾기
    if (GetMesh())
    {
        Shield = Cast<UStaticMeshComponent>(GetMesh()->GetChildComponent(0)); // 첫 번째 자식이 Shield라고 가정
    }
}

void APlayerTankCharacter::SetIsAlly(bool InIsAlly)
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

void APlayerTankCharacter::Act()
{
	// 향후 Animation notify 와 연계하여 방패 들고 내리는 것 구현할 예정
}
