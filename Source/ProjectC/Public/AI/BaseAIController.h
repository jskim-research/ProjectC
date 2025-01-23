// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:

protected:
	virtual void BeginPlay() override;
	
	// Logic 관리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* DefaultBehaviorTree;

	// 상태 관리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBlackboardData* DefaultBlackboardData;

};
