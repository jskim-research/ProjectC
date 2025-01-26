// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"

ABaseAIController::ABaseAIController()
{
	// 모든 변수를 초기화해주는 것이 좋지만 BehaviorTree, BlackboardData 는 외부에서 설정하는 것 가정
	
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
	bool IsAllSet = BehaviorTree && BlackboardData;

	if (IsAllSet)
	{
		UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
		UseBlackboard(BlackboardData, BlackboardComponent);
		RunBehaviorTree(BehaviorTree);

		UE_LOG(LogTemp, Log, TEXT("AIController is ready."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController is not ready."));
	}
}
