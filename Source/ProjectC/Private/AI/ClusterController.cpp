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

	ClusterBlackboard = NewObject<UClusterBlackboard>();

	DealerBehaviorTree = NewObject<UDealerBehaviorTree>();
	HealerBehaviorTree = NewObject<UHealerBehaviorTree>();
	TankBehaviorTree = NewObject<UTankBehaviorTree>();

	DealerBehaviorTree->SetBlackboard(ClusterBlackboard);
	HealerBehaviorTree->SetBlackboard(ClusterBlackboard);
	TankBehaviorTree->SetBlackboard(ClusterBlackboard);

	ClusterCommand = EClusterCommand::Hold;
}

void AClusterController::Possess(UCluster* InSelfCluster)
{
	SelfCluster = InSelfCluster;
}

void AClusterController::UpdateBlackboard()
{
	if (ClusterBlackboard)
	{
		ClusterBlackboard->SetAllyClusterAverageLocation(SelfCluster->GetClusterAvergeLocation());
		ClusterBlackboard->SetAllyDealerAverageLocation(SelfCluster->GetDealerAverageLocation());
		ClusterBlackboard->SetAllyHealerAverageLocation(SelfCluster->GetHealerAverageLocation());
		ClusterBlackboard->SetAllyTankAverageLocation(SelfCluster->GetTankAverageLocation());

		ClusterBlackboard->SetEnemyClusterAverageLocation(SelfCluster->GetTargetCluster()->GetClusterAvergeLocation());
		ClusterBlackboard->SetEnemyDealerAverageLocation(SelfCluster->GetTargetCluster()->GetDealerAverageLocation());
		ClusterBlackboard->SetEnemyHealerAverageLocation(SelfCluster->GetTargetCluster()->GetHealerAverageLocation());
		ClusterBlackboard->SetEnemyTankAverageLocation(SelfCluster->GetTargetCluster()->GetTankAverageLocation());
	}
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
		UpdateBlackboard();
		TankBehaviorTree->Run(SelfCluster);
		DealerBehaviorTree->Run(SelfCluster);
		HealerBehaviorTree->Run(SelfCluster);
	}
}
