// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPCCharacter.h"

ANPCCharacter::ANPCCharacter()
{
	static ConstructorHelpers::FClassFinder<UCharacterInfoWidget> InfoWidgetFinder(TEXT("/Game/Blueprints/UI/Widgets/WBP_CharacterInfo"));

	InfoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InfoWidget"));
	InfoWidgetComponent->SetupAttachment(RootComponent);
	
	if (InfoWidgetFinder.Succeeded())
	{
		InfoWidgetComponent->SetWidgetClass(InfoWidgetFinder.Class);
		InfoWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		InfoWidgetComponent->SetDrawSize(FVector2D(200, 50));
		InfoWidgetComponent->SetRelativeLocation(FVector(0, 0, 125));
	}
}

void ANPCCharacter::SetMaxHealth(float InMaxHealth)
{
	Super::SetMaxHealth(InMaxHealth);

	if (InfoWidget)
	{
		float Ratio = (GetMaxHealth() == 0) ? 0 : GetCurrentHealth() / GetMaxHealth();
		InfoWidget->SetHPRatio(Ratio);
	}
}

void ANPCCharacter::SetCurrentHealth(float InCurrentHealth)
{
	Super::SetCurrentHealth(InCurrentHealth);

	if (InfoWidget)
	{
		float Ratio = (GetMaxHealth() == 0) ? 0 : GetCurrentHealth() / GetMaxHealth();
		InfoWidget->SetHPRatio(Ratio);
	}
}

void ANPCCharacter::SetUIVisibility(bool InVisibility)
{
	if (InVisibility)
	{
		InfoWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		InfoWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();

	InfoWidget = Cast<UCharacterInfoWidget>(InfoWidgetComponent->GetWidget());
}
