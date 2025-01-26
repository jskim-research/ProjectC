// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ClusterController.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Data/Cluster.h"

AClusterController::AClusterController()
{
	// Tick 활성화
	PrimaryActorTick.bCanEverTick = true;
	
	// Tick 간격 설정 (예: 0.5초마다 호출)
	PrimaryActorTick.TickInterval = 0.5f;
}

void AClusterController::Possess(UCluster* InSelfCluster)
{
	SelfCluster = InSelfCluster;
}

void AClusterController::Test()
{
	if (!SelfCluster || !SelfCluster->GetTargetCluster())
	{
		UE_LOG(LogTemp, Warning, TEXT("AClusterController::Test: SelfCluster or TargetCluster is not initialized."));
		return;
	}

	// 탱커 -> 딜각차단 전술

	// 우리팀 딜러 또는 힐러 - 상대팀 딜러간의 각도 계산 후 중간 지점 방어

	FVector AllyLocation = FVector::ZeroVector;
	FVector EnemyLocation = FVector::ZeroVector;

	for (ABaseCharacter* Character : SelfCluster->GetDealerArray())
	{
		AllyLocation += Character->GetActorLocation();
	}

	AllyLocation /= SelfCluster->GetDealerArray().Num();

	for (ABaseCharacter* Character : SelfCluster->GetTargetCluster()->GetDealerArray())
	{
		EnemyLocation += Character->GetActorLocation();
	}

	EnemyLocation /= SelfCluster->GetTargetCluster()->GetDealerArray().Num();

	FVector DirectionToEnemy = (EnemyLocation - AllyLocation);
	DirectionToEnemy.Normalize();
	FVector OrthogonalDirection = DirectionToEnemy;
	OrthogonalDirection.X = DirectionToEnemy.Y;
	OrthogonalDirection.Y = - DirectionToEnemy.X;
	// OrthogonalDirection.Z = -1 / DirectionToEnemy.Z;
	OrthogonalDirection.Normalize();

	UE_LOG(LogTemp, Warning, TEXT("Test: %f, Dir: %f %f %f"), DirectionToEnemy.Dot(OrthogonalDirection), OrthogonalDirection.X, OrthogonalDirection.Y, OrthogonalDirection.Z);

	float DefenseLineOffset = 500;  // 아군으로부터 방어선 offset 거리
	float DefenseLineInterval = 300;  // 방어선 간격

	// 탱커 움직이기
	TArray<ABaseCharacter*> TankArray = SelfCluster->GetTankArray();
	for (int i = 0; i < TankArray.Num(); i++)
	{
		AAIController* Controller = Cast<AAIController>(TankArray[i]->GetController());
		if (Controller)
		{
			Controller->GetPathFollowingComponent()->OnRequestFinished.AddLambda(
				[Controller, AllyLocation, EnemyLocation](FAIRequestID RequestID, const FPathFollowingResult& Result)
				{
					if (Result.IsSuccess())
					{
						FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(AllyLocation, EnemyLocation);
						Controller->GetPawn()->SetActorRotation(LookAtRotation);
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("AClusterController::Test:MoveToLocation failed or was aborted."));
					}
				});
			Controller->MoveToLocation(AllyLocation + DirectionToEnemy * DefenseLineOffset + (i - int(TankArray.Num()/2)) * OrthogonalDirection * DefenseLineInterval);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AClusterController::Test: AIController is not found."));
		}
	}

}

void AClusterController::Tick(float DeltaTime)
{
	// 상태 체크 => 전술 변경
	// 이벤트 기반으로 바꾸는 게 효율적일수도 (혼합해서 사용하거나)
}
