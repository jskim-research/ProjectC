// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AI/ClusterController.h"
#include "Characters/BaseCharacter.h"
#include "Enums/RoleType.h"
#include "CustomMathUtils/CustomClusterUtilities.h"
#include "Cluster.generated.h"




UCLASS()
class PROJECTC_API UCluster : public UObject
{
	GENERATED_BODY()
	
public:
	UCluster();
	void InitCluster(UWorld* InWorld);
	void AddUnit(ABaseCharacter* InCharacter, ERoleType Type);
	void SetTargetCluster(UCluster* InTargetCluster);

	UCluster* GetTargetCluster();
	TArray<ABaseCharacter*>& GetTankArray();
	TArray<ABaseCharacter*>& GetHealerArray();
	TArray<ABaseCharacter*>& GetDealerArray();
	AClusterController* GetClusterController();

	FVector GetClusterAvergeLocation() const;
	FVector GetDealerAverageLocation() const;
	FVector GetHealerAverageLocation() const;
	FVector GetTankAverageLocation() const;

	uint32 GetAllUnitNum();
	uint32 GetDealerNum();
	uint32 GetHealerNum();
	uint32 GetTankNum();

private:
	UPROPERTY()
	AClusterController* ClusterController;

	UPROPERTY()
	TArray<ABaseCharacter*> TankArray;

	UPROPERTY()
	TArray<ABaseCharacter*> HealerArray;

	UPROPERTY()
	TArray<ABaseCharacter*> DealerArray;

	UPROPERTY()
	UCluster* TargetCluster;

};
