// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ClusterController.h"
#include "AIController.h"
#include "CustomMathUtils/CustomProbabilityUtilities.h"
#include "Data/Cluster.h"

AClusterController::AClusterController()
{
	// Tick 활성화
	PrimaryActorTick.bCanEverTick = true;
	
	// Tick 간격 설정 (예: 0.5초마다 호출)
	PrimaryActorTick.TickInterval = 0.5f;

	DealerBehaviorTree = NewObject<UDealerBehaviorTree>();
	HealerBehaviorTree = NewObject<UHealerBehaviorTree>();
	TankBehaviorTree = NewObject<UTankBehaviorTree>();

	ClusterCommand = EClusterCommand::Holding;
}

void AClusterController::Possess(UCluster* InSelfCluster)
{
	SelfCluster = InSelfCluster;
}

EClusterCommand AClusterController::GetClusterCommand() const
{
	return ClusterCommand;
}

void AClusterController::Tick(float DeltaTime)
{
	// 상태 체크 => 전술 변경
	// 이벤트 기반으로 바꾸는 게 효율적일수도 (혼합해서 사용하거나)

	if (SelfCluster && SelfCluster->GetTargetCluster())
	{
		TankBehaviorTree->Run(SelfCluster);
		DealerBehaviorTree->Run(SelfCluster);
		HealerBehaviorTree->Run(SelfCluster);
	}
}
