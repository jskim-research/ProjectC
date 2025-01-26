// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Cluster.h"

UCluster::UCluster()
{
}

void UCluster::Test()
{
	ClusterController->Test();
}

void UCluster::InitCluster(UWorld* InWorld)
{
	if (InWorld)
	{
		ClusterController = InWorld->SpawnActor<AClusterController>();

		if (ClusterController)
		{
			ClusterController->Possess(this);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UCluster::InitCluster: ClusterController Spawn Failed."));
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
		DealerArray.Add(InCharacter);
		break;
	case ERoleType::Tank:
		TankArray.Add(InCharacter);
		break;
	case ERoleType::Healer:
		HealerArray.Add(InCharacter);
		break;
	case ERoleType::None:
		UE_LOG(LogTemp, Warning, TEXT("UCluster::AddUnit: ERoleType::None is not supported."));
		break;
	}
}

void UCluster::SetTargetCluster(UCluster* InTargetCluster)
{
	TargetCluster = InTargetCluster;
}

UCluster* UCluster::GetTargetCluster()
{
	return TargetCluster;
}

TArray<ABaseCharacter*>& UCluster::GetTankArray()
{
	return TankArray;
}

TArray<ABaseCharacter*>& UCluster::GetHealerArray()
{
	return HealerArray;
}

TArray<ABaseCharacter*>& UCluster::GetDealerArray()
{
	return DealerArray;
}
