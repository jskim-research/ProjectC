// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums/ClusterCommand.h"
#include "Enums/DealerBehaviorState.h"
#include "Enums/HealerBehaviorState.h"
#include "Enums/TankBehaviorState.h"
#include "Characters/BaseCharacter.h"
#include "CustomMathUtils/CustomProbabilityUtilities.h"
#include "BaseBehaviorTree.generated.h"

class UCluster;

UCLASS(Abstract)
class PROJECTC_API UBaseBehaviorTree : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void Run(UCluster* AllyCluster) PURE_VIRTUAL(UBaseBehaviorTree::Run,);

	// Condition(ABaseCharacter* Target, ABaseCharacter* Character) -> Character 가 Target 보다 우선순위가 높은 경우 true 반환, 이외 false 반환
	ABaseCharacter* GetMostProperTarget(const TArray<ABaseCharacter*>& Characters, TFunctionRef<bool(const ABaseCharacter*, const ABaseCharacter*)> Condition) const;
	static bool HealPriority(const ABaseCharacter* Target, const ABaseCharacter* Character);
	static bool AttackPriority(const ABaseCharacter* Target, const ABaseCharacter* Character);

};
