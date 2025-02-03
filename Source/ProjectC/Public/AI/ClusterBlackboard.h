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
	void SetClusterAverageLocation(const FVector& InAverageLocation);
	const FVector& GetClusterAverageLocation() const;

	void SetDealerAverageLocation(const FVector& InAverageLocation);
	const FVector& GetDealerAverageLocation() const;

	void SetHealerAverageLocation(const FVector& InAverageLocation);
	const FVector& GetHealerAverageLocation() const;

	void SetTankAverageLocation(const FVector& InAverageLocation);
	const FVector& GetTankAverageLocation() const;

	void SetDealerHealerAverageLocation(const FVector& InAverageLocation);
	const FVector& GetDealerHealerAverageLocation() const;

private:
	FVector ClusterAverageLocation;
	FVector DealerAverageLocation;
	FVector HealerAverageLocation;
	FVector TankAverageLocation;
	FVector DealerHealerAverageLocation;
};
