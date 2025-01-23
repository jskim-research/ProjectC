// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/DemoGameMode.h"

ADemoGameMode::ADemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_PlayerTankCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADemoGameMode::BeginPlay()
{
}
