// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTrees/DealerBehaviorTree.h"
#include "Data/Cluster.h"

void UDealerBehaviorTree::Run(UCluster* AllyCluster)
{
	if (AllyCluster->GetDealerNum() == 0)
	{
		return;
	}

	AClusterController* Controller = AllyCluster->GetClusterController();

	switch (Controller->GetClusterCommand())
	{
	case EClusterCommand::Hold:
		TacticsHold(AllyCluster);
		break;

	case EClusterCommand::Charge:
		TacticsCharge(AllyCluster);
		break;
	}

	// TacticsDealerAttack(AllyCluster);
	/*
	EDealerBehaviorState DealerBehaviorState = GetDealerBehaviorState();

	switch (DealerBehaviorState)
	{
	case EDealerBehaviorState::Attack:
		TacticsDealerAttack();
		break;
	}
	*/
}


void UDealerBehaviorTree::TacticsDealerAttack(UCluster* AllyCluster)
{
	UCluster* TargetCluster = AllyCluster->GetTargetCluster();
	ABaseCharacter* AttackTarget = nullptr;
	float Distance;
	bool ShouldEvade = false;
	AAIController* Controller;
	int32 EvasionProbability = 50;  // %, 회피 기동 시전할 확률

	// 공격 대상 선정
	if (!TargetCluster->GetHealerArray().IsEmpty())
	{
		AttackTarget = GetAttackTarget(TargetCluster->GetHealerArray());
	}
	else if (!TargetCluster->GetDealerArray().IsEmpty())
	{
		AttackTarget = GetAttackTarget(TargetCluster->GetDealerArray());
	}
	else if (!TargetCluster->GetTankArray().IsEmpty())
	{
		AttackTarget = GetAttackTarget(TargetCluster->GetTankArray());
	}

	if (AttackTarget)
	{
		for (ABaseCharacter* Character : AllyCluster->GetDealerArray())
		{
			Controller = Cast<AAIController>(Character->GetController());
			Distance = FVector::Distance(Character->GetActorLocation(), AttackTarget->GetActorLocation());
			ShouldEvade = false;

			if (!Controller)
			{
				// 플레이어가 포함된 경우 controller 가 없을 수 있음
				continue;
			}

			Controller->SetFocalPoint(AttackTarget->GetActorLocation());

			if (Character->GetCurrentHealth() <= Character->GetMaxHealth() * 0.5)
			{
				// 피가 별로 없을 때 확률적으로 회피 시전
				if (FCustomProbabilityUtilities::IsProbabilitySuccessful(EvasionProbability))
					ShouldEvade = true;
			}

			if (ShouldEvade)
			{
				FVector RandomEvasionPoint = FCustomProbabilityUtilities::GenerateRandomSphericalPoint(300);

				Controller->MoveToLocation(Character->GetActorLocation() + RandomEvasionPoint);
			}
			else
			{
				if (Distance < Character->GetRange())
				{
					Controller->StopMovement();
					Character->Act();
				}
				else
				{
					Controller->MoveToLocation(AttackTarget->GetActorLocation());
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UDealerBehaviorTree::TacticsDealerAttack: Attack target is not found."));
	}
}

void UDealerBehaviorTree::TacticsHold(UCluster* AllyCluster)
{
	UCluster* EnemyCluster = AllyCluster->GetTargetCluster();
	const UClusterBlackboard* EnemyBlackboard = EnemyCluster->GetClusterController()->GetBlackboard();
	
	if (AllyCluster->GetTankNum() > 0)
	{
		// 탱커 군집 평균점과의 거리가 0.5 * Range ~ 0.75 * Range 이도록 조정
		MoveBehindDefenseLine(AllyCluster->GetDealerArray(), ClusterBlackboard->GetTankAverageLocation(), EnemyBlackboard->GetClusterAverageLocation());
	}
	else
	{
		// 탱커 군집이 없으면 딜러 군집이 최전선
		const FVector& AllyAverageLocation = ClusterBlackboard->GetClusterAverageLocation();
		const FVector& EnemyAverageLocation =EnemyBlackboard->GetClusterAverageLocation();

		MoveToDefenseLine(AllyCluster->GetDealerArray(), AllyAverageLocation, EnemyAverageLocation, EnemyAverageLocation, 0.4, 300);
	}
	
	PerformAttack(AllyCluster);
}

void UDealerBehaviorTree::TacticsCharge(UCluster* AllyCluster)
{
	// 적군 딜러 > 힐러 > 탱커 우선순위로 따라다니면서 공격
	UCluster* EnemyCluster = AllyCluster->GetTargetCluster();
	const UClusterBlackboard* EnemyBlackboard = EnemyCluster->GetClusterController()->GetBlackboard();
	AAIController* Controller;
	const FVector* TargetClusterLocation = nullptr;

	if (EnemyCluster->GetDealerNum() > 0)
	{
		TargetClusterLocation = &EnemyBlackboard->GetDealerAverageLocation();
	}
	else if (EnemyCluster->GetHealerNum() > 0)
	{
		TargetClusterLocation = &EnemyBlackboard->GetHealerAverageLocation();
	}
	else if (EnemyCluster->GetTankNum() > 0)
	{
		TargetClusterLocation = &EnemyBlackboard->GetTankAverageLocation();
	}

	if (TargetClusterLocation)
	{
		for (ABaseCharacter* Character : AllyCluster->GetDealerArray())
		{
			// 돌격 진형이므로 일부러 Range 보다 가깝게 이동시킴
			float Range = 0.5 * Character->GetRange();

			if (FVector::Dist(Character->GetActorLocation(), *TargetClusterLocation) < Range)
			{
				// 사정 거리 안에 있는 경우 공격 수행
				PerformAttack(AllyCluster);
			}
			else
			{
				// 사정 거리 바깥에 있는 경우 + 이동중이지 않은 경우 이동 수행
				Controller = Cast<AAIController>(Character->GetController());
				if (Controller && Controller->GetMoveStatus() != EPathFollowingStatus::Moving)
				{
					FVector RandomPoint = FCustomProbabilityUtilities::GenerateRandomSphericalPoint(Range);
					Controller->MoveToLocation(*TargetClusterLocation + RandomPoint);
				}

			}
		}
	}
}

void UDealerBehaviorTree::PerformAttack(UCluster* AllyCluster)
{
	AAIController* Controller;
	UCluster* EnemyCluster = AllyCluster->GetTargetCluster();

	// 딜하기 (naive 하게 우선 구현)
	for (ABaseCharacter* Dealer : AllyCluster->GetDealerArray())
	{
		// 자신으로부터 Range 내에 있으면서 가장 피가 적은 Unit 선택
		ABaseCharacter* Target = nullptr;
		float Range = Dealer->GetRange();

		for (ABaseCharacter* Character : EnemyCluster->GetDealerArray())
		{
			bool HasMorePriority = (!Target || Target->GetCurrentHealth() > Character->GetCurrentHealth()) && FVector::Dist(Character->GetActorLocation(), Dealer->GetActorLocation()) <= Range;
			if (HasMorePriority)
			{
				Target = Character;
			}
		}

		for (ABaseCharacter* Character : EnemyCluster->GetHealerArray())
		{
			bool HasMorePriority = (!Target || Target->GetCurrentHealth() > Character->GetCurrentHealth()) && FVector::Dist(Character->GetActorLocation(), Dealer->GetActorLocation()) <= Range;
			if (HasMorePriority)
			{
				Target = Character;
			}
		}

		for (ABaseCharacter* Character : EnemyCluster->GetTankArray())
		{
			bool HasMorePriority = (!Target || Target->GetCurrentHealth() > Character->GetCurrentHealth()) && FVector::Dist(Character->GetActorLocation(), Dealer->GetActorLocation()) <= Range;
			if (HasMorePriority)
			{
				Target = Character;
			}
		}

		if (Target)
		{
			Controller = Cast<AAIController>(Dealer->GetController());
			if (Controller)
			{
				Controller->SetFocalPoint(Target->GetActorLocation());
				Dealer->Act();
			}
		}
	}
}

ABaseCharacter* UDealerBehaviorTree::GetAttackTarget(TArray<ABaseCharacter*>& Characters) const
{
	return GetMostProperTarget(Characters, AttackPriority);
}


EDealerBehaviorState UDealerBehaviorTree::GetDealerBehaviorState() const
{
	return EDealerBehaviorState::Attack;
}
