// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/DemoGameMode.h"
#include "Data/Grid.h"
#include "GameInstances/CoreGameInstance.h"

ADemoGameMode::ADemoGameMode()
{
	// set default pawn class to our Blueprinted character
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_PlayerTankCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_PlayerDealerCharacter"));
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_PlayerHealerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADemoGameMode::BeginPlay()
{
	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADemoGameMode::BeginPlay: World is not found."));
		return;
	}

	UCoreGameInstance* GI = Cast<UCoreGameInstance>(World->GetGameInstance());

	if (GI)
	{
		FGrid Map(5, 5);
		Map(0, 4) = FGridTile(ERoleType::Dealer, false);
		Map(0, 3) = FGridTile(ERoleType::Healer, false);
		Map(0, 2) = FGridTile(ERoleType::Dealer, true);

		Map(1, 2) = FGridTile(ERoleType::Tank, false);
		Map(0, 1) = FGridTile(ERoleType::Tank, false);
		Map(0, 0) = FGridTile(ERoleType::Tank, false);

		Map(4, 2) = FGridTile(ERoleType::Dealer, true);
		Map(4, 1) = FGridTile(ERoleType::Dealer, true);
		Map(4, 0) = FGridTile(ERoleType::Healer, true);
		
		Map(3, 1) = FGridTile(ERoleType::Tank, true);
		Map(3, 2) = FGridTile(ERoleType::Tank, true);

		GI->SpawnGrid(World, Map);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ADemoGameMode::BeginPlay: UCoreGameInstance is not found."));
	}
}
