// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ClusterBlackboard.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API UClusterBlackboard : public UObject
{
	GENERATED_BODY()
	
public:
	void SetAllyClusterAverageLocation(const FVector& InAverageLocation);
	const FVector& GetAllyClusterAverageLocation() const;

	void SetAllyDealerAverageLocation(const FVector& InAverageLocation);
	const FVector& GetAllyDealerAverageLocation() const;

	void SetAllyHealerAverageLocation(const FVector& InAverageLocation);
	const FVector& GetAllyHealerAverageLocation() const;

	void SetAllyTankAverageLocation(const FVector& InAverageLocation);
	const FVector& GetAllyTankAverageLocation() const;

	void SetEnemyClusterAverageLocation(const FVector& InAverageLocation);
	const FVector& GetEnemyClusterAverageLocation() const;

	void SetEnemyDealerAverageLocation(const FVector& InAverageLocation);
	const FVector& GetEnemyDealerAverageLocation() const;

	void SetEnemyHealerAverageLocation(const FVector& InAverageLocation);
	const FVector& GetEnemyHealerAverageLocation() const;

	void SetEnemyTankAverageLocation(const FVector& InAverageLocation);
	const FVector& GetEnemyTankAverageLocation() const;

private:
	FVector AllyClusterAverageLocation;
	FVector AllyDealerAverageLocation;
	FVector AllyHealerAverageLocation;
	FVector AllyTankAverageLocation;

	FVector EnemyClusterAverageLocation;
	FVector EnemyDealerAverageLocation;
	FVector EnemyHealerAverageLocation;
	FVector EnemyTankAverageLocation;
};
