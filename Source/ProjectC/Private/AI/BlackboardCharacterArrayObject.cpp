// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BlackboardCharacterArrayObject.h"

void UBlackboardCharacterArrayObject::AddCharacter(ABaseCharacter* InCharacter)
{
	CharacterArray.Add(InCharacter);
}
