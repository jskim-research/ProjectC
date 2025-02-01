// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Enums/DealerBehaviorState.h"
#include "Enums/HealerBehaviorState.h"
#include "Enums/TankBehaviorState.h"
#include "Enums/ClusterCommand.h"
#include "Navigation/PathFollowingComponent.h"
#include "Math/UnrealMathUtility.h"
#include "BehaviorTrees/BaseBehaviorTree.h"
#include "BehaviorTrees/DealerBehaviorTree.h"
#include "BehaviorTrees/HealerBehaviorTree.h"
#include "BehaviorTrees/TankBehaviorTree.h"
#include "AI/ClusterBlackboard.h"
#include "ClusterController.generated.h"


class UCluster;

UCLASS()
class PROJECTC_API AClusterController : public AActor
{
	GENERATED_BODY()

public:
	AClusterController();
	void Possess(UCluster* InSelfCluster);
	void UpdateBlackboard();

	EClusterCommand GetClusterCommand() const;

protected:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	UCluster* SelfCluster;

	UPROPERTY()
	UBaseBehaviorTree* DealerBehaviorTree;

	UPROPERTY()
	UBaseBehaviorTree* HealerBehaviorTree;

	UPROPERTY()
	UBaseBehaviorTree* TankBehaviorTree;

	EClusterCommand ClusterCommand;

	UPROPERTY()
	UClusterBlackboard* ClusterBlackboard;
};
