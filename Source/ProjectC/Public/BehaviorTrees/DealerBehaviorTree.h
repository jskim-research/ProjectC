// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTrees/BaseBehaviorTree.h"
#include "DealerBehaviorTree.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API UDealerBehaviorTree : public UBaseBehaviorTree
{
	GENERATED_BODY()
	
public:
	virtual void Run(UCluster* AllyCluster) override;

	// 아군 딜러 공격 전술
	void TacticsDealerAttack(UCluster* AllyCluster);
	ABaseCharacter* GetAttackTarget(TArray<ABaseCharacter*>& Characters) const;
	
	EDealerBehaviorState GetDealerBehaviorState() const;
};
