// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Cluster.h"
#include <array>

UCluster::UCluster()
{
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

AClusterController* UCluster::GetClusterController()
{
	return ClusterController;
}

FVector UCluster::GetClusterAvergeLocation() const
{
	// 메모리 복사 없이 다수 array 엮는 방식
	// CalculateAverageLocation 의 경우 Actor = nullptr 인 경우 계산에서 제외한 것 유의
	std::array<TArrayView<ABaseCharacter *const>, 3> CombinedViews = { MakeArrayView(DealerArray), MakeArrayView(HealerArray), MakeArrayView(TankArray) };
	return FCustomClusterUtilities::CalculateAverageLocation<ABaseCharacter, 3>(CombinedViews);
}

FVector UCluster::GetDealerAverageLocation() const
{
	return FCustomClusterUtilities::CalculateAverageLocation(DealerArray);
}

FVector UCluster::GetHealerAverageLocation() const
{
	return FCustomClusterUtilities::CalculateAverageLocation(HealerArray);
}

FVector UCluster::GetTankAverageLocation() const
{
	return FCustomClusterUtilities::CalculateAverageLocation(TankArray);
}

uint32 UCluster::GetAllUnitNum()
{
	// Actor = nullptr 인 경우 고려하지 않음
	return GetDealerNum() + GetHealerNum() + GetTankNum();
}

uint32 UCluster::GetDealerNum()
{
	return DealerArray.Num();
}

uint32 UCluster::GetHealerNum()
{
	return HealerArray.Num();
}

uint32 UCluster::GetTankNum()
{
	return TankArray.Num();
}
