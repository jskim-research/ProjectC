// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Enums/DealerBehaviorState.h"
#include "Enums/HealerBehaviorState.h"
#include "Enums/TankBehaviorState.h"
#include "Navigation/PathFollowingComponent.h"
#include "Math/UnrealMathUtility.h"
#include "ClusterController.generated.h"


class UCluster;

UCLASS()
class PROJECTC_API AClusterController : public AActor
{
	GENERATED_BODY()

public:
	AClusterController();
	void Possess(UCluster* InSelfCluster);
	// 상대 딜러 딜각 차단 전술
	void TacticsTankDealDefense();
	// Healer -> Target 힐각 차단 전술
	void TacticsTankHealDefense(TArray<ABaseCharacter*>& Healer, TArray<ABaseCharacter*>& Target);
	// 아군 딜러 공격 전술
	void TacticsDealerAttack();
	// 아군 힐러 힐 전술
	void TacticsHealerHeal();

	EDealerBehaviorState GetDealerBehaviorState() const;
	EHealerBehaviorState GetHealerBehaviorState() const;
	ETankBehaviorState GetTankBehaviorState() const;

	void RunDealerBehaviorTree();
	void RunHealerBehaviorTree();
	void RunTankBehaviorTree();

	void MoveTankToDefenseLine(const FVector& StartLocation, const FVector& EndLocation, const FVector& LookAtLocation, float Ratio, float Interval, TFunction<void(FAIRequestID, const FPathFollowingResult&)> OnArrivalCallback = nullptr);
	ABaseCharacter* GetAttackTarget(TArray<ABaseCharacter*>& Characters) const;
	ABaseCharacter* GetHealTarget();
	// Condition(ABaseCharacter* Target, ABaseCharacter* Character) -> Character 가 Target 보다 우선순위가 높은 경우 true 반환, 이외 false 반환
	ABaseCharacter* GetMostProperTarget(const TArray<ABaseCharacter*>& Characters, TFunctionRef<bool(const ABaseCharacter*, const ABaseCharacter*)> Condition) const;
	static bool HealPriority(const ABaseCharacter* Target, const ABaseCharacter* Character);
	static bool AttackPriority(const ABaseCharacter* Target, const ABaseCharacter* Character);

protected:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	UCluster* SelfCluster;

	UPROPERTY()
	TArray<ABaseCharacter*> CachedHealTargets;
};
