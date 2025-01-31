// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTrees/DealerBehaviorTree.h"
#include "Data/Cluster.h"

void UDealerBehaviorTree::Run(UCluster* AllyCluster)
{
	TacticsDealerAttack(AllyCluster);
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
				FVector RandomEvasionPoint = FCustomProbabilityUtilities::GenerateRandomSphericalPoint();

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

ABaseCharacter* UDealerBehaviorTree::GetAttackTarget(TArray<ABaseCharacter*>& Characters) const
{
	return GetMostProperTarget(Characters, AttackPriority);
}


EDealerBehaviorState UDealerBehaviorTree::GetDealerBehaviorState() const
{
	return EDealerBehaviorState::Attack;
}
