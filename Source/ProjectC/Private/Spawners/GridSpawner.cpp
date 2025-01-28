// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/GridSpawner.h"
#include "AIController.h"
#include "GameInstances/CoreGameInstance.h"
#include "Kismet/GameplayStatics.h"

UGridSpawner::UGridSpawner()
{
	static ConstructorHelpers::FClassFinder<ABaseCharacter> TankBPClass(TEXT("/Game/Blueprints/Characters/BP_NPCTankCharacter"));
	static ConstructorHelpers::FClassFinder<ABaseCharacter> DealerBPClass(TEXT("/Game/Blueprints/Characters/BP_NPCDealerCharacter"));
	static ConstructorHelpers::FClassFinder<ABaseCharacter> HealerBPClass(TEXT("/Game/Blueprints/Characters/BP_NPCHealerCharacter"));

	if (TankBPClass.Succeeded())
	{
		TankBlueprint = TankBPClass.Class;
	}

	if (DealerBPClass.Succeeded())
	{
		DealerBlueprint = DealerBPClass.Class;
	}

	if (HealerBPClass.Succeeded())
	{
		HealerBlueprint = HealerBPClass.Class;
	}
}

void UGridSpawner::SpawnGrid(UWorld* InWorld, const FGrid& InGrid)
{
	if (InGrid.RowSize == 0 || InGrid.ColSize == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGridSpawner::SpawnGrid: Grid size should not be zero."));
		return;
	}

	if (!InWorld)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGridSpawner::SpawnGrid: World is not found."));
		return;
	}

	// Tag Floor 로 해둔 바닥이 있고 그 위에 Spawn 하는 것 가정
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(InWorld, FName("Floor"), FoundActors);

	if (FoundActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGridSpawner::SpawnGrid: Mesh with tag 'Floor' is not found."));
	}
	else
	{
		// 첫 번째 Floor 만 사용
		AActor* Actor = FoundActors[0];

		UStaticMeshComponent* StaticMeshComponent = Actor->FindComponentByClass<UStaticMeshComponent>();

		if (StaticMeshComponent)
		{
			FBoxSphereBounds Bounds = StaticMeshComponent->Bounds;

			FVector Min = Bounds.Origin - Bounds.BoxExtent; // 최소값
			FVector Max = Bounds.Origin + Bounds.BoxExtent; // 최대값

			// Top, Bottom, Left, Right 계산 (x, y 평면 기준)
			// 평면 사각형 가정
			// 시작점 (Left, Top)
			// 끝점 (Right, Bottom)

			// 언리얼 좌표계는 왼손 좌표계
			// (Left, Top) 은 오른쪽 위, (Right, Bottom) 은 왼쪽 아래
			float Top = Max.Y;
			float Bottom = Min.Y;
			float Left = Min.X;
			float Right = Max.X;

			float Height = Top - Bottom;
			float Width = Right - Left;

			// PositionRatioX = 0.5 인 경우 Tile 중간 지점에 배치
			// 랜덤하게 배치하려면 Ratio 랜덤하게 바꾸면 됨
			float PositionRatioX = 0.5;
			float PositionRatioY = 0.5;

			float TileSizeX = Width / InGrid.ColSize;
			float TileSizeY = Height / InGrid.RowSize;

			for (int Row = 0; Row < InGrid.RowSize; Row++)
			{
				for (int Col = 0; Col < InGrid.ColSize; Col++)
				{
					FVector Position;
					
					// 왼손 좌표계 고려해서 왼쪽 위에서 오른쪽 아래로 나열되도록 수식 정리
					Position.X = Right - (Width / InGrid.ColSize) * (Col + PositionRatioX);
					Position.Y = Top - (Height / InGrid.RowSize) * (Row + PositionRatioY);
					Position.Z = Max.Z;  // 바닥 위에 생성되도록 함

					Spawn(InWorld, Position, InGrid(Row, Col));
				}
			}

			UE_LOG(LogTemp, Log, TEXT("%f %f %f %f"), Top, Left, Bottom, Right);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UGridSpawner::SpawnGrid: %s does not have static mesh component."), *Actor->GetName());
		}

	}
}

void UGridSpawner::Spawn(UWorld* InWorld, FVector Position, const FGridTile& TileInfo)
{
	FActorSpawnParameters SpawnParams;
	FRotator Rotation = FRotator::ZeroRotator;
	ABaseCharacter* SpawnedCharacter = nullptr;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParams.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;

	switch (TileInfo.RoleType)
	{
		case ERoleType::None:
			break;
		case ERoleType::Tank:
			SpawnedCharacter = InWorld->SpawnActor<ABaseCharacter>(*TankBlueprint, Position, Rotation, SpawnParams);
			// 임의로 지금은 HP 여기서 바로 설정 (나중에 구조 좀 바꿔야함)
			SpawnedCharacter->SetMaxHealth(200);
			SpawnedCharacter->SetCurrentHealth(200);
			SpawnedCharacter->SetRange(1000);
			break;
		case ERoleType::Dealer:
			SpawnedCharacter = InWorld->SpawnActor<ABaseCharacter>(DealerBlueprint, Position, Rotation, SpawnParams);
			SpawnedCharacter->SetMaxHealth(100);
			SpawnedCharacter->SetCurrentHealth(50);
			SpawnedCharacter->SetRange(1000);
			break;
		case ERoleType::Healer:
			SpawnedCharacter = InWorld->SpawnActor<ABaseCharacter>(HealerBlueprint, Position, Rotation, SpawnParams);
			SpawnedCharacter->SetMaxHealth(150);
			SpawnedCharacter->SetCurrentHealth(150);
			SpawnedCharacter->SetRange(1000);
			break;
	}

	// 전역 AI 는 명령을 내리고 실제 수행은 개별 AI 가 진행 (e.g., 특정 지점까지 이동)
	if (SpawnedCharacter)
	{
		AAIController* AIController = InWorld->SpawnActor<AAIController>();
		if (AIController)
		{
			AIController->Possess(SpawnedCharacter);
		}

		UCoreGameInstance* GI = Cast<UCoreGameInstance>(InWorld->GetGameInstance());
		if (GI)
		{
			GI->AddUnitToCluster(SpawnedCharacter, TileInfo.RoleType, TileInfo.IsAlly);
		}

		FLinearColor TeamColor = (TileInfo.IsAlly) ? FLinearColor::Blue : FLinearColor::Red;
		SpawnedCharacter->SetBaseColor(TeamColor);
	}
}
