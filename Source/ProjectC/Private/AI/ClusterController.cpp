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
}

void AClusterController::Possess(UCluster* InSelfCluster)
{
	SelfCluster = InSelfCluster;
}

void AClusterController::TacticsTankDealDefense()
{
	// 탱커 -> 딜각차단 전술
	// 우리팀 딜러 또는 힐러 - 상대팀 딜러간의 각도 계산 후 중간 지점 방어

	FVector AllyLocation = FVector::ZeroVector;
	FVector EnemyLocation = FVector::ZeroVector;

	for (ABaseCharacter* Character : SelfCluster->GetDealerArray())
	{
		AllyLocation += Character->GetActorLocation();
	}

	for (ABaseCharacter* Character : SelfCluster->GetHealerArray())
	{
		AllyLocation += Character->GetActorLocation();
	}

	// DivideByZero 에러 대비 최소값 1 설정
	AllyLocation /= FMath::Max((SelfCluster->GetDealerArray().Num() + SelfCluster->GetHealerArray().Num()), 1);

	for (ABaseCharacter* Character : SelfCluster->GetTargetCluster()->GetDealerArray())
	{
		EnemyLocation += Character->GetActorLocation();
	}

	// DivideByZero 에러 대비 최소값 1 설정
	EnemyLocation /= FMath::Max(SelfCluster->GetTargetCluster()->GetDealerArray().Num(), 1);

	MoveTankToDefenseLine(AllyLocation, EnemyLocation, EnemyLocation, 0.5, 300);
}

void AClusterController::TacticsTankHealDefense(TArray<ABaseCharacter*>& Healer, TArray<ABaseCharacter*>& Target)
{
	// 탱커 -> Target 힐각 차단 전술

	if (&Healer == &Target)
	{
		// 힐돕힐 차단
		if (Healer.Num() >= 2)
		{
			// 임의로 첫번째, 두번째부터 고립 (나중에 개선하면 좋을듯)
			MoveTankToDefenseLine(Healer[0]->GetActorLocation(), Healer[1]->GetActorLocation(), Healer[0]->GetActorLocation(), 0.5, 150);
		}
	}
	else
	{
		// 상대 힐러진 - Target 사이 차단

		FVector HealerLocation = FVector::ZeroVector;
		FVector TargetLocation = FVector::ZeroVector;

		for (ABaseCharacter* Character : Healer)
		{
			HealerLocation += Character->GetActorLocation();
		}

		HealerLocation /= FMath::Max(Healer.Num(), 1);

		for (ABaseCharacter* Character : Target)
		{
			TargetLocation += Character->GetActorLocation();
		}

		TargetLocation /= FMath::Max(Target.Num(), 1);

		MoveTankToDefenseLine(HealerLocation, TargetLocation, HealerLocation, 0.5, 300);
	}
}

void AClusterController::TacticsDealerAttack()
{
	// 공격 대상 선정
	UCluster* TargetCluster = SelfCluster->GetTargetCluster();
	ABaseCharacter* AttackTarget = nullptr;
	float Distance;
	bool ShouldEvade = false;
	AAIController* Controller;
	int32 EvasionProbability = 50;  // %, 회피 기동 시전할 확률

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
		for (ABaseCharacter* Character : SelfCluster->GetDealerArray())
		{
			Controller = Cast<AAIController>(Character->GetController());
			Distance = FVector::Distance(Character->GetActorLocation(), AttackTarget->GetActorLocation());
			ShouldEvade = false;

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
		UE_LOG(LogTemp, Warning, TEXT("AClusterController::TacticsDealerAttack: Attack target is not found."));
	}

	
}

EDealerBehaviorState AClusterController::GetDealerBehaviorState() const
{
	return EDealerBehaviorState::Attack;
}

EHealerBehaviorState AClusterController::GetHealerBehaviorState() const
{
	return EHealerBehaviorState::None;
}

ETankBehaviorState AClusterController::GetTankBehaviorState() const
{
	UCluster* TargetCluster = SelfCluster->GetTargetCluster();

	// 딜각 차단 조건
	bool ShouldDefenseDeal = true;
	// 아군 딜러 또는 힐러가 한 명 이상 존재하는가?
	ShouldDefenseDeal = ShouldDefenseDeal && !(SelfCluster->GetDealerArray().IsEmpty() && SelfCluster->GetHealerArray().IsEmpty());
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

void AClusterController::RunDealerBehaviorTree()
{
	EDealerBehaviorState DealerBehaviorState = GetDealerBehaviorState();

	switch (DealerBehaviorState)
	{
	case EDealerBehaviorState::Attack:
		TacticsDealerAttack();
		break;
	}
}

void AClusterController::RunHealerBehaviorTree()
{
}

void AClusterController::RunTankBehaviorTree()
{
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
}

void AClusterController::MoveTankToDefenseLine(const FVector& StartLocation, const FVector& EndLocation, const FVector& LookAtLocation, float Ratio, float Interval, TFunction<void(FAIRequestID, const FPathFollowingResult&)> OnArrivalCallback)
{
	FVector StartToTarget = (EndLocation - StartLocation);
	StartToTarget.Normalize();
	FVector OrthogonalDirection = StartToTarget;
	OrthogonalDirection.X = StartToTarget.Y;
	OrthogonalDirection.Y = -StartToTarget.X;
	OrthogonalDirection.Normalize();

	// 시작점 - 끝점 에서 Ratio 부분에 방어선 구축 (Ratio = 0.5 인 경우 힐러와 Target 중앙)
	float DefenseLineOffset = FVector::Distance(StartLocation, EndLocation) * Ratio;
	
	// 탱커 움직여서 실제 방어선 구축
	TArray<ABaseCharacter*>& TankArray = SelfCluster->GetTankArray();
	for (int i = 0; i < TankArray.Num(); i++)
	{
		AAIController* Controller = Cast<AAIController>(TankArray[i]->GetController());

		if (Controller)
		{
			if (OnArrivalCallback)
			{
				Controller->GetPathFollowingComponent()->OnRequestFinished.AddLambda(
					OnArrivalCallback
				);

			}
			Controller->MoveToLocation(StartLocation + StartToTarget * DefenseLineOffset + (i - int(TankArray.Num() / 2)) * OrthogonalDirection * Interval);
			Controller->SetFocalPoint(LookAtLocation);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AClusterController::Test: AIController is not found."));
		}
	}
}

ABaseCharacter* AClusterController::GetAttackTarget(TArray<ABaseCharacter*>& Characters) const
{
	ABaseCharacter* Target = nullptr;

	for (ABaseCharacter* Character : Characters)
	{
		if (Target)
		{
			if (Target->GetCurrentHealth() > Character->GetCurrentHealth())
				Target = Character;
		}
		else
		{
			Target = Character;
		}
	}

	return Target;
}

void AClusterController::Tick(float DeltaTime)
{
	// 상태 체크 => 전술 변경
	// 이벤트 기반으로 바꾸는 게 효율적일수도 (혼합해서 사용하거나)

	if (SelfCluster && SelfCluster->GetTargetCluster())
	{
		RunTankBehaviorTree();
		RunDealerBehaviorTree();
	}
}
