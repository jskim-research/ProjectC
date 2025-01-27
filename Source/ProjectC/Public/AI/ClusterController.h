// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Enums/DealerBehaviorState.h"
#include "Enums/HealerBehaviorState.h"
#include "Enums/TankBehaviorState.h"
#include "Navigation/PathFollowingComponent.h"
#include "ClusterController.generated.h"


class UCluster;

UCLASS()
class PROJECTC_API AClusterController : public AActor
{
	GENERATED_BODY()

public:
	AClusterController();
	void Possess(UCluster* InSelfCluster);
	void TacticsTankDealDefense();
	void TacticsTankHealDefense(TArray<ABaseCharacter*>& Healer, TArray<ABaseCharacter*>& Target);

	EDealerBehaviorState GetDealerBehaviorState() const;
	EHealerBehaviorState GetHealerBehaviorState() const;
	ETankBehaviorState GetTankBehaviorState() const;

	void RunDealerBehaviorTree();
	void RunHealerBehaviorTree();
	void RunTankBehaviorTree();

	void MoveTankToDefenseLine(FVector StartLocation, FVector EndLocation, FVector LookAtLocation, float Ratio, float Interval, TFunction<void(FAIRequestID, const FPathFollowingResult&)> OnArrivalCallback = nullptr);

protected:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	UCluster* SelfCluster;
};
