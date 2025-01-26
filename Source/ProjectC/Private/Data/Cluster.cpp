// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Cluster.h"

UCluster::UCluster()
{
	static ConstructorHelpers::FClassFinder<ABaseAIController> BPClass(TEXT("/Game/Blueprints/AI/BP_ClusterAIController"));
	if (BPClass.Class != NULL)
	{
		AIControllerClass = BPClass.Class;
	}

	TankArrayObject = NewObject<UBlackboardCharacterArrayObject>();
	HealerArrayObject = NewObject<UBlackboardCharacterArrayObject>();
	DealerArrayObject = NewObject<UBlackboardCharacterArrayObject>();
}

void UCluster::InitCluster(UWorld* World)
{
	if (World)
	{
		if (AIControllerClass)
		{
			ClusterController = World->SpawnActor<ABaseAIController>(AIControllerClass);
			ClusterController->GetBlackboardComponent()->SetValueAsObject("TankArray", TankArrayObject);
			ClusterController->GetBlackboardComponent()->SetValueAsObject("HealerArray", HealerArrayObject);
			ClusterController->GetBlackboardComponent()->SetValueAsObject("DealerArray", DealerArrayObject);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UCluster::InitCluster: AIControllerClass is not found."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UCluster::InitCluster: World is not found."));
	}
}

void UCluster::AddUnit(ABaseCharacter* InCharacter, ERoleType Type)
{
	switch (Type)
	{
	case ERoleType::Dealer:
		DealerArrayObject->AddCharacter(InCharacter);
		break;
	case ERoleType::Tank:
		TankArrayObject->AddCharacter(InCharacter);
		break;
	case ERoleType::Healer:
		HealerArrayObject->AddCharacter(InCharacter);
		break;
	case ERoleType::None:
		UE_LOG(LogTemp, Warning, TEXT("UCluster::AddUnit: ERoleType::None is not supported."));
		break;
	}
}
