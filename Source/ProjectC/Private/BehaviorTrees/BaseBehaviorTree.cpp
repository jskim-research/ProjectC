// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTrees/BaseBehaviorTree.h"


ABaseCharacter* UBaseBehaviorTree::GetMostProperTarget(const TArray<ABaseCharacter*>& Characters, TFunctionRef<bool(const ABaseCharacter*, const ABaseCharacter*)> Condition) const
{
	ABaseCharacter* Target = nullptr;

	for (ABaseCharacter* Character : Characters)
	{
		if (Target)
		{
			// Character 우선 순위 > Target 우선순위 일 때 Target 변경
			if (Character && Condition(Target, Character))
				Target = Character;
		}
		else
		{
			Target = Character;
		}
	}
	return Target;
}

bool UBaseBehaviorTree::HealPriority(const ABaseCharacter* Target, const ABaseCharacter* Character)
{
	// HP 가 작은 경우 Character 의 힐 우선순위 인정
	if (Target->GetCurrentHealth() > Character->GetCurrentHealth()) return true;
	return false;
}

bool UBaseBehaviorTree::AttackPriority(const ABaseCharacter* Target, const ABaseCharacter* Character)
{
	// HP 가 작은 경우 Character 의 공격 우선순위 인정
	if (Target->GetCurrentHealth() > Character->GetCurrentHealth()) return true;
	return false;
}