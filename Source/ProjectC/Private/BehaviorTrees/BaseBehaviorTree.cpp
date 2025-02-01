// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTrees/BaseBehaviorTree.h"
#include "Data/Cluster.h"


ABaseCharacter* UBaseBehaviorTree::GetMostProperTarget(const TArray<ABaseCharacter*>& Characters, TFunctionRef<bool(const ABaseCharacter*, const ABaseCharacter*)> Condition) const
{
	ABaseCharacter* Target = nullptr;

	for (ABaseCharacter* Character : Characters)
	{
		if (Target)
		{
			// Character 우선 순위 > Target 우선순위 일 때 Target 변경
			if (Character && Condition(Target, Character))
				Target = Character;
		}
		else
		{
			Target = Character;
		}
	}
	return Target;
}

void UBaseBehaviorTree::MoveToDefenseLine(TArray<ABaseCharacter*>& Characters, const FVector& StartLocation, const FVector& EndLocation, const FVector& LookAtLocation, float Ratio, float Interval, TFunction<void(FAIRequestID, const FPathFollowingResult&)> OnArrivalCallback)
{
	FVector StartToTarget = (EndLocation - StartLocation);
	StartToTarget.Normalize();
	FVector OrthogonalDirection = StartToTarget;
	OrthogonalDirection.X = StartToTarget.Y;
	OrthogonalDirection.Y = -StartToTarget.X;
	OrthogonalDirection.Normalize();

	// 시작점 - 끝점 에서 Ratio 부분에 방어선 구축 (Ratio = 0.5 인 경우 힐러와 Target 중앙)
	float DefenseLineOffset = FVector::Distance(StartLocation, EndLocation) * Ratio;

	// 캐릭터 움직여서 실제 방어선 구축
	for (int i = 0; i < Characters.Num(); i++)
	{
		AAIController* Controller = Cast<AAIController>(Characters[i]->GetController());

		if (Controller)
		{
			if (OnArrivalCallback)
			{
				Controller->GetPathFollowingComponent()->OnRequestFinished.AddLambda(
					OnArrivalCallback
				);

			}
			Controller->MoveToLocation(StartLocation + StartToTarget * DefenseLineOffset + (i - int(Characters.Num() / 2)) * OrthogonalDirection * Interval);
			Controller->SetFocalPoint(LookAtLocation);
		}
	}
}

void UBaseBehaviorTree::MoveBehindDefenseLine(TArray<ABaseCharacter*>& Characters, const FVector& DefenseLocation, const FVector& EnemyLocation)
{
	AAIController* Controller;

	for (ABaseCharacter* Character : Characters)
	{
		Controller = Cast<AAIController>(Character->GetController());

		if (!Controller)
		{
			// 플레이어가 포함된 경우 controller 가 없을 수 있음
			continue;
		}

		FVector V1 = EnemyLocation - DefenseLocation;
		FVector V2 = Character->GetActorLocation() - DefenseLocation;

		V1.Normalize();
		V2.Normalize();

		float Cos = V1.Dot(V2);
		float Dist = FVector::Dist(Character->GetActorLocation(), DefenseLocation);
		float Range = Character->GetRange();

		if (Cos > 0)
		{
			// 아군이 방어선 바깥, 적진에 있는 것이므로 방어선 안으로 들어오게 해야함
			FVector Destination = Character->GetActorLocation() - V1 * 2 * Dist * Cos;

			Controller->MoveToLocation(Destination);
		}
		else
		{
			if (0.5 * Range <= Dist && Dist <= 0.75 * Range)
			{
				// No need to move				
			}
			else
			{
				// 넉넉잡아 0.65 * Range 까지 이동하도록 함
				FVector Destination = DefenseLocation + V2 * 0.65 * Range;

				Controller->MoveToLocation(Destination);
			}

		}
	}
}

void UBaseBehaviorTree::SetBlackboard(UClusterBlackboard* InClusterBlackboard)
{
	ClusterBlackboard = InClusterBlackboard;
}

bool UBaseBehaviorTree::HealPriority(const ABaseCharacter* Target, const ABaseCharacter* Character)
{
	// HP 가 작은 경우 Character 의 힐 우선순위 인정
	if (Target->GetCurrentHealth() > Character->GetCurrentHealth()) return true;
	return false;
}

bool UBaseBehaviorTree::AttackPriority(const ABaseCharacter* Target, const ABaseCharacter* Character)
{
	// HP 가 작은 경우 Character 의 공격 우선순위 인정
	if (Target->GetCurrentHealth() > Character->GetCurrentHealth()) return true;
	return false;
}