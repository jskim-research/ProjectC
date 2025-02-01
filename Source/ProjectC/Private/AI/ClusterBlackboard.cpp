// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ClusterBlackboard.h"

void UClusterBlackboard::SetAllyClusterAverageLocation(const FVector& InAverageLocation)
{
	AllyClusterAverageLocation = InAverageLocation;
}

const FVector& UClusterBlackboard::GetAllyClusterAverageLocation() const
{
	return AllyClusterAverageLocation;
}

void UClusterBlackboard::SetAllyDealerAverageLocation(const FVector& InAverageLocation)
{
	AllyDealerAverageLocation = InAverageLocation;
}

const FVector& UClusterBlackboard::GetAllyDealerAverageLocation() const
{
	return AllyDealerAverageLocation;
}

void UClusterBlackboard::SetAllyHealerAverageLocation(const FVector& InAverageLocation)
{
	AllyHealerAverageLocation = InAverageLocation;
}

const FVector& UClusterBlackboard::GetAllyHealerAverageLocation() const
{
	return AllyHealerAverageLocation;
}

void UClusterBlackboard::SetAllyTankAverageLocation(const FVector& InAverageLocation)
{
	AllyTankAverageLocation = InAverageLocation;
}

const FVector& UClusterBlackboard::GetAllyTankAverageLocation() const
{
	return AllyTankAverageLocation;
}

void UClusterBlackboard::SetEnemyClusterAverageLocation(const FVector& InAverageLocation)
{
	EnemyClusterAverageLocation = InAverageLocation;
}

const FVector& UClusterBlackboard::GetEnemyClusterAverageLocation() const
{
	return EnemyClusterAverageLocation;
}

void UClusterBlackboard::SetEnemyDealerAverageLocation(const FVector& InAverageLocation)
{
	EnemyDealerAverageLocation = InAverageLocation;
}

const FVector& UClusterBlackboard::GetEnemyDealerAverageLocation() const
{
	return EnemyDealerAverageLocation;
}

void UClusterBlackboard::SetEnemyHealerAverageLocation(const FVector& InAverageLocation)
{
	EnemyHealerAverageLocation = InAverageLocation;
}

const FVector& UClusterBlackboard::GetEnemyHealerAverageLocation() const
{
	return EnemyHealerAverageLocation;
}

void UClusterBlackboard::SetEnemyTankAverageLocation(const FVector& InAverageLocation)
{
	EnemyTankAverageLocation = InAverageLocation;
}

const FVector& UClusterBlackboard::GetEnemyTankAverageLocation() const
{
	return EnemyTankAverageLocation;
}
