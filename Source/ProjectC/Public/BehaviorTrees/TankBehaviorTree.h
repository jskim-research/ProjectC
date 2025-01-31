// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTrees/BaseBehaviorTree.h"
#include "TankBehaviorTree.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API UTankBehaviorTree : public UBaseBehaviorTree
{
	GENERATED_BODY()
	
public:
	virtual void Run(UCluster* AllyCluster) override;

protected:
	// 상대 딜러 딜각 차단 전술
	void TacticsTankDealDefense(UCluster* AllyCluster, UCluster* EnemyCluster);
	// AllyTank 가 EnemyHealer -> EnemyTarget 힐 차단
	void TacticsTankHealDefense(TArray<ABaseCharacter*>& AllyTank, TArray<ABaseCharacter*>& EnemyHealer, TArray<ABaseCharacter*>& EnemyTarget);
	void TacticsHold(UCluster* AllyCluster);

	ETankBehaviorState GetTankBehaviorState(UCluster* AllyCluster, UCluster* EnemyCluster) const;
};
