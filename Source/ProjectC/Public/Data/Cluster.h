// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AI/BaseAIController.h"
#include "Enums/RoleType.h"
#include "Cluster.generated.h"




UCLASS()
class PROJECTC_API UCluster : public UObject
{
	GENERATED_BODY()
	
public:
	UCluster();
	// Cluster AIController 활성화
	void InitCluster(UWorld* World);
	void AddUnit(ABaseCharacter* InCharacter, ERoleType Type);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBlackboardCharacterArrayObject* TankArrayObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBlackboardCharacterArrayObject* HealerArrayObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBlackboardCharacterArrayObject* DealerArrayObject;

private:
	TSubclassOf<ABaseAIController> AIControllerClass;
	
	UPROPERTY()
	ABaseAIController* ClusterController;
	// 전투 대상 클러스터 index => CoreGameInstance 에서 전체 클러스터 관리
	unsigned int TargetClusterID = 0;
};
