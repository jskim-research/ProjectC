// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BlackboardCharacterArrayObject.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABaseAIController();
	// 순서에 민감해서 캡슐화함
	void RunController(UBlackboardCharacterArrayObject* TankArray, UBlackboardCharacterArrayObject* DealerArray, UBlackboardCharacterArrayObject* HealerArray);

protected:	
	// Logic 관리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;

	// 상태 관리 (딜, 힐, 탱 HP 등 상태 기준 BehaviorTree 행동 결정됨)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBlackboardData* BlackboardData;

	void InitClusterBlackboard();
	void RunClusterBehaviorTree();
};
