// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTrees/BaseBehaviorTree.h"
#include "HealerBehaviorTree.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API UHealerBehaviorTree : public UBaseBehaviorTree
{
	GENERATED_BODY()
	
public:
	virtual void Run(UCluster* AllyCluster) override;
	// 아군 힐러 힐 전술
	void TacticsHealerHeal(UCluster* AllyCluster);
	ABaseCharacter* GetHealTarget(UCluster* AllyCluster);
	EHealerBehaviorState GetHealerBehaviorState() const;

private:
	UPROPERTY()
	TArray<ABaseCharacter*> CachedHealTargets;
};
