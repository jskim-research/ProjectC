// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTrees/TankBehaviorTree.h"
#include "Data/Cluster.h"

void UTankBehaviorTree::Run(UCluster* AllyCluster)
{
	if (AllyCluster->GetTankNum() == 0)
	{
		// TankBehaviorTree 의 핵심인 Tank 가 없는 경우 behavior tree 수행할 이유 없음
		return;
	}

	AClusterController* Controller = AllyCluster->GetClusterController();

	switch (Controller->GetClusterCommand())
	{
	case EClusterCommand::Hold:
		TacticsHold(AllyCluster);
		break;

	case EClusterCommand::Charge:
		break;
	}

	// UCluster* EnemyCluster = AllyCluster->GetTargetCluster();
	// TacticsTankDealDefense(AllyCluster, EnemyCluster);
	// TacticsTankHealDefense(AllyCluster->GetTankArray(), EnemyCluster->GetHealerArray(), EnemyCluster->GetTankArray());

	/*
	ETankBehaviorState TankBehaviorState = GetTankBehaviorState();

	switch (TankBehaviorState)
	{
	case ETankBehaviorState::DealDefense:
		TacticsTankDealDefense();
		break;

	case ETankBehaviorState::HealToDealerDefense:
		TacticsTankHealDefense(SelfCluster->GetTargetCluster()->GetHealerArray(), SelfCluster->GetTargetCluster()->GetDealerArray());
		break;

	case ETankBehaviorState::HealToHealerDefense:
		TacticsTankHealDefense(SelfCluster->GetTargetCluster()->GetHealerArray(), SelfCluster->GetTargetCluster()->GetHealerArray());
		break;

	case ETankBehaviorState::HealToTankDefense:
		TacticsTankHealDefense(SelfCluster->GetTargetCluster()->GetHealerArray(), SelfCluster->GetTargetCluster()->GetTankArray());
		break;
	}
	*/
}

void UTankBehaviorTree::TacticsTankDealDefense(UCluster* AllyCluster, UCluster* EnemyCluster)
{
	// 탱커 -> 딜각차단 전술
	// 우리팀 딜러 또는 힐러 - 상대팀 딜러간의 각도 계산 후 중간 지점 방어

	FVector AllyLocation = FVector::ZeroVector;
	FVector EnemyLocation = FVector::ZeroVector;

	for (ABaseCharacter* Character : AllyCluster->GetDealerArray())
	{
		AllyLocation += Character->GetActorLocation();
	}

	for (ABaseCharacter* Character : AllyCluster->GetHealerArray())
	{
		AllyLocation += Character->GetActorLocation();
	}

	// DivideByZero 에러 대비 최소값 1 설정
	AllyLocation /= FMath::Max((AllyCluster->GetDealerArray().Num() + AllyCluster->GetHealerArray().Num()), 1);

	for (ABaseCharacter* Character : EnemyCluster->GetDealerArray())
	{
		EnemyLocation += Character->GetActorLocation();
	}

	// DivideByZero 에러 대비 최소값 1 설정
	EnemyLocation /= FMath::Max(EnemyCluster->GetDealerArray().Num(), 1);

	MoveToDefenseLine(AllyCluster->GetTankArray(), AllyLocation, EnemyLocation, EnemyLocation, 0.5, 300);
}

void UTankBehaviorTree::TacticsTankHealDefense(TArray<ABaseCharacter*>& AllyTank, TArray<ABaseCharacter*>& EnemyHealer, TArray<ABaseCharacter*>& EnemyTarget)
{
	// 탱커 -> Target 힐각 차단 전술

	if (&EnemyHealer == &EnemyTarget)
	{
		// 힐돕힐 차단
		if (EnemyHealer.Num() >= 2)
		{
			// 임의로 첫번째, 두번째부터 고립 (나중에 개선하면 좋을듯)
			MoveToDefenseLine(AllyTank, EnemyHealer[0]->GetActorLocation(), EnemyHealer[1]->GetActorLocation(), EnemyHealer[0]->GetActorLocation(), 0.5, 150);
		}
	}
	else
	{
		// 상대 힐러진 - Target 사이 차단

		FVector HealerLocation = FVector::ZeroVector;
		FVector TargetLocation = FVector::ZeroVector;

		for (ABaseCharacter* Character : EnemyHealer)
		{
			HealerLocation += Character->GetActorLocation();
		}

		HealerLocation /= FMath::Max(EnemyHealer.Num(), 1);

		for (ABaseCharacter* Character : EnemyTarget)
		{
			TargetLocation += Character->GetActorLocation();
		}

		TargetLocation /= FMath::Max(EnemyTarget.Num(), 1);

		MoveToDefenseLine(AllyTank, HealerLocation, TargetLocation, HealerLocation, 0.5, 300);
	}
}

void UTankBehaviorTree::TacticsHold(UCluster* AllyCluster)
{
	// 상대 군집 평균과 아군 군집 평균 사이를 defense line 으로 정하고 holding
	UCluster* EnemyCluster = AllyCluster->GetTargetCluster();

	// 상대 군집 또는 아군 군집이 없는 경우 전략 수행 X
	if (AllyCluster->GetAllUnitNum() == 0 || EnemyCluster->GetAllUnitNum() == 0)
		return;

	const FVector& AllyAverageLocation = ClusterBlackboard->GetAllyClusterAverageLocation();
	const FVector& EnemyAverageLocation = ClusterBlackboard->GetEnemyClusterAverageLocation();

	MoveToDefenseLine(AllyCluster->GetTankArray(), AllyAverageLocation, EnemyAverageLocation, EnemyAverageLocation, 0.4, 300);
}

ETankBehaviorState UTankBehaviorTree::GetTankBehaviorState(UCluster* AllyCluster, UCluster* EnemyCluster) const
{
	UCluster* TargetCluster = AllyCluster->GetTargetCluster();

	// 딜각 차단 조건
	bool ShouldDefenseDeal = true;
	// 아군 딜러 또는 힐러가 한 명 이상 존재하는가?
	ShouldDefenseDeal = ShouldDefenseDeal && !(AllyCluster->GetDealerArray().IsEmpty() && AllyCluster->GetHealerArray().IsEmpty());
	// 상대 딜러가 한 명 이상 존재하는가?
	ShouldDefenseDeal = ShouldDefenseDeal && !TargetCluster->GetDealerArray().IsEmpty();

	if (ShouldDefenseDeal)
	{
		return ETankBehaviorState::DealDefense;
	}
	else if (!TargetCluster->GetHealerArray().IsEmpty())
	{
		// 힐각 차단 (상대 탱 > 딜 > 힐 우선순위)
		if (!TargetCluster->GetTankArray().IsEmpty())
		{
			return ETankBehaviorState::HealToTankDefense;
		}
		else if (!TargetCluster->GetDealerArray().IsEmpty())
		{
			return ETankBehaviorState::HealToDealerDefense;
		}
		else if (TargetCluster->GetHealerArray().Num() >= 2)
		{
			return ETankBehaviorState::HealToHealerDefense;
		}
	}
	return ETankBehaviorState::None;
}