#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EHealerBehaviorState : uint8
{
    None UMETA(DisplayName = "None"),
    // 현재는 전황 상관없이 힐 상황만 가정
    Heal UMETA(DisplayName = "Heal")
};