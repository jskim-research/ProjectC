// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClusterController.generated.h"


class UCluster;

UCLASS()
class PROJECTC_API AClusterController : public AActor
{
	GENERATED_BODY()

public:
	AClusterController();
	void Possess(UCluster* InSelfCluster);

protected:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	UCluster* SelfCluster;
};
