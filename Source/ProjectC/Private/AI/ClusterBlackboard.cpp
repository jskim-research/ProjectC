// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ClusterBlackboard.h"

void UClusterBlackboard::SetClusterAverageLocation(const FVector& InAverageLocation)
{
	ClusterAverageLocation = InAverageLocation;
}

const FVector& UClusterBlackboard::GetClusterAverageLocation() const
{
	return ClusterAverageLocation;
}

void UClusterBlackboard::SetDealerAverageLocation(const FVector& InAverageLocation)
{
	DealerAverageLocation = InAverageLocation;
}

const FVector& UClusterBlackboard::GetDealerAverageLocation() const
{
	return DealerAverageLocation;
}

void UClusterBlackboard::SetHealerAverageLocation(const FVector& InAverageLocation)
{
	HealerAverageLocation = InAverageLocation;
}

const FVector& UClusterBlackboard::GetHealerAverageLocation() const
{
	return HealerAverageLocation;
}

void UClusterBlackboard::SetTankAverageLocation(const FVector& InAverageLocation)
{
	TankAverageLocation = InAverageLocation;
}

const FVector& UClusterBlackboard::GetTankAverageLocation() const
{
	return TankAverageLocation;
}
