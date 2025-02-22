// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTrees/HealerBehaviorTree.h"
#include "Data/Cluster.h"

void UHealerBehaviorTree::Run(UCluster* AllyCluster)
{
	if (AllyCluster->GetHealerNum() == 0)
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

	// TacticsHealerHeal(AllyCluster);
	/*
	EHealerBehaviorState HealerBehaviorState = GetHealerBehaviorState();

	switch (HealerBehaviorState)
	{
	case EHealerBehaviorState::Heal:
		TacticsHealerHeal();
		break;
	}
	*/
}


void UHealerBehaviorTree::TacticsHealerHeal(UCluster* AllyCluster)
{
	ABaseCharacter* HealTarget = nullptr;
	float Distance;
	bool ShouldEvade = false;
	AAIController* Controller;
	int32 EvasionProbability = 50;  // %, 회피 기동 시전할 확률

	// 힐 대상 선정
	HealTarget = GetHealTarget(AllyCluster);

	if (HealTarget)
	{
		for (ABaseCharacter* Character : AllyCluster->GetHealerArray())
		{
			// Cast 비용 있으니 미리 Cache 해두자
			Controller = Cast<AAIController>(Character->GetController());
			Distance = FVector::Distance(Character->GetActorLocation(), HealTarget->GetActorLocation());
			ShouldEvade = false;

			if (!Controller)
			{
				// 플레이어가 포함된 경우 controller 가 없을 수 있음
				continue;
			}

			Controller->SetFocalPoint(HealTarget->GetActorLocation());

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
					Controller->MoveToLocation(HealTarget->GetActorLocation());
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UHealerBehaviorTree::TacticsHealerHeal: Heal target is not found."));
	}
}

void UHealerBehaviorTree::TacticsHold(UCluster* AllyCluster)
{
	const UClusterBlackboard* EnemyBlackboard = AllyCluster->GetTargetCluster()->GetClusterController()->GetBlackboard();

	if (AllyCluster->GetDealerNum() > 0)
	{	
		MoveBehindDefenseLine(AllyCluster->GetHealerArray(), ClusterBlackboard->GetDealerAverageLocation(), EnemyBlackboard->GetClusterAverageLocation());
	}
	else if (AllyCluster->GetTankNum() > 0)
	{
		MoveBehindDefenseLine(AllyCluster->GetHealerArray(), ClusterBlackboard->GetTankAverageLocation(), EnemyBlackboard->GetClusterAverageLocation());
	}
	else
	{

	}

	PerformHeal(AllyCluster);	
}

void UHealerBehaviorTree::TacticsCharge(UCluster* AllyCluster)
{
	// 아군 딜러 > 힐러 > 탱커 우선순위로 따라다니면서 힐
	AAIController* Controller;
	const FVector* TargetClusterLocation = nullptr;

	if (AllyCluster->GetDealerNum() > 0)
	{
		TargetClusterLocation = &ClusterBlackboard->GetDealerAverageLocation();
	}
	else if (AllyCluster->GetHealerNum() > 0)
	{
		TargetClusterLocation = &ClusterBlackboard->GetHealerAverageLocation();
	}
	else if (AllyCluster->GetTankNum() > 0)
	{
		TargetClusterLocation = &ClusterBlackboard->GetTankAverageLocation();
	}

	if (TargetClusterLocation)
	{
		for (ABaseCharacter* Character : AllyCluster->GetHealerArray())
		{
			// 돌격 진형이므로 일부러 Range 보다 가깝게 이동시킴
			float Range = 0.5 * Character->GetRange();

			if (FVector::Dist(Character->GetActorLocation(), *TargetClusterLocation) < Range)
			{
				// 사정 거리 안에 있는 경우 공격 수행
				PerformHeal(AllyCluster);
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

void UHealerBehaviorTree::PerformHeal(UCluster* AllyCluster)
{
	AAIController* Controller;

	// 힐하기 (naive 하게 우선 구현)
	for (ABaseCharacter* Healer : AllyCluster->GetHealerArray())
	{
		// 자신으로부터 Range 내에 있으면서 가장 피가 적은 Unit 선택
		ABaseCharacter* Target = nullptr;
		float Range = Healer->GetRange();

		for (ABaseCharacter* Character : AllyCluster->GetDealerArray())
		{
			bool HasMorePriority = (!Target || Target->GetCurrentHealth() > Character->GetCurrentHealth()) && FVector::Dist(Character->GetActorLocation(), Healer->GetActorLocation()) <= Range;
			if (HasMorePriority)
			{
				Target = Character;
			}
		}

		for (ABaseCharacter* Character : AllyCluster->GetHealerArray())
		{
			bool HasMorePriority = (!Target || Target->GetCurrentHealth() > Character->GetCurrentHealth()) && FVector::Dist(Character->GetActorLocation(), Healer->GetActorLocation()) <= Range;
			if (HasMorePriority)
			{
				Target = Character;
			}
		}

		for (ABaseCharacter* Character : AllyCluster->GetTankArray())
		{
			bool HasMorePriority = (!Target || Target->GetCurrentHealth() > Character->GetCurrentHealth()) && FVector::Dist(Character->GetActorLocation(), Healer->GetActorLocation()) <= Range;
			if (HasMorePriority)
			{
				Target = Character;
			}
		}

		if (Target && Target != Healer)
		{
			Controller = Cast<AAIController>(Healer->GetController());
			if (Controller)
			{
				Controller->SetFocalPoint(Target->GetActorLocation());
				Healer->Act();
			}
		}
	}
}

ABaseCharacter* UHealerBehaviorTree::GetHealTarget(UCluster* AllyCluster)
{
	// 탱, 딜, 힐 전부 체력 확인 후 가장 체력 적은 대상 반환
	CachedHealTargets.Reset();

	CachedHealTargets.Add(GetMostProperTarget(AllyCluster->GetDealerArray(), HealPriority));
	CachedHealTargets.Add(GetMostProperTarget(AllyCluster->GetHealerArray(), HealPriority));
	CachedHealTargets.Add(GetMostProperTarget(AllyCluster->GetTankArray(), HealPriority));

	return GetMostProperTarget(CachedHealTargets, HealPriority);
}

EHealerBehaviorState UHealerBehaviorTree::GetHealerBehaviorState() const
{
	return EHealerBehaviorState::Heal;
}