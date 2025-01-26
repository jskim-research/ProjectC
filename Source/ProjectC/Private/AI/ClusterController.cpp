// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ClusterController.h"

AClusterController::AClusterController()
{
	// Tick 활성화
	PrimaryActorTick.bCanEverTick = true;
	
	// Tick 간격 설정 (예: 0.5초마다 호출)
	PrimaryActorTick.TickInterval = 0.5f;
}

void AClusterController::Possess(UCluster* InSelfCluster)
{
	SelfCluster = InSelfCluster;
}

void AClusterController::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("Tick: %f"), DeltaTime);
}
