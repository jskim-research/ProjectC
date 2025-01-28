#pragma once

#include "CoreMinimal.h"

// 정확히는 DealerClusterBehaviorState 인듯
UENUM(BlueprintType)
enum class EDealerBehaviorState : uint8
{
    None UMETA(DisplayName = "None"),
    // 현재는 전황 상관없이 공격 상황만 가정
    Attack UMETA(DisplayName = "Attack"),
};