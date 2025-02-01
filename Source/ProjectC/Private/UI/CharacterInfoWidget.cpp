// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterInfoWidget.h"

void UCharacterInfoWidget::SetName(const FString& InName)
{
	Name->SetText(FText::FromString(InName));
}

void UCharacterInfoWidget::SetHPRatio(float InRatio)
{
	InRatio = FMath::Clamp(InRatio, 0.0, 1.0);
	HPBar->SetPercent(InRatio);
}
