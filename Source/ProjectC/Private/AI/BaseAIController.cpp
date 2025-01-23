// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"

void ABaseAIController::BeginPlay()
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (DefaultBlackboardData && DefaultBehaviorTree && BlackboardComponent)
	{
		UseBlackboard(DefaultBlackboardData, BlackboardComponent);
		RunBehaviorTree(DefaultBehaviorTree);
	}
}
