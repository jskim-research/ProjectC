// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"

ABaseAIController::ABaseAIController()
{
	// 모든 변수를 초기화해주는 것이 좋지만 BehaviorTree, BlackboardData 는 외부에서 설정하는 것 가정
	
}

void ABaseAIController::InitClusterBlackboard()
{
	if (BlackboardData)
	{
		UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
		UseBlackboard(BlackboardData, BlackboardComponent);
		UE_LOG(LogTemp, Log, TEXT("ABaseAIController::InitClusterBlackboard: Blackboard initialized."));
	}
	else
	{

		UE_LOG(LogTemp, Warning, TEXT("ABaseAIController::InitClusterBlackboard: BlackboardData is not found."));
	}
}

void ABaseAIController::RunClusterBehaviorTree()
{
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		UE_LOG(LogTemp, Log, TEXT("ABaseAIController::RunClusterBehaviorTree: BehaviorTree runs."));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("ABaseAIController::RunClusterBehaviorTree: BehaviorTree is not found."));
	}
}

void ABaseAIController::RunController(UBlackboardCharacterArrayObject* TankArray, UBlackboardCharacterArrayObject* DealerArray, UBlackboardCharacterArrayObject* HealerArray)
{
	// Blackboard 를 먼저 활성화 시켜야 BehaviorTree 블루프린트 receive activation ai event 에서
	// Blackboard 데이터 기반 작업 정상 수행 가능
	InitClusterBlackboard();
	GetBlackboardComponent()->SetValueAsObject("TankArray", TankArray);
	GetBlackboardComponent()->SetValueAsObject("HealerArray", HealerArray);
	GetBlackboardComponent()->SetValueAsObject("DealerArray", DealerArray);
	RunClusterBehaviorTree();
}
