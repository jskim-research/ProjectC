#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETankBehaviorState : uint8
{
    None UMETA(DisplayName = "None"),
    // 상대 딜러 딜각 차단
    DealDefense UMETA(DisplayName = "DealDefense"),
    // 상대 힐러 -> 상대 딜러 힐각 차단
    HealToDealerDefense UMETA(DisplayName = "HealToDealerDefense"),
    // 상대 힐러 -> 상대 힐러 힐각 차단
    HealToHealerDefense UMETA(DisplayName = "HealToHealerDefense"),
    // 상대 힐러 -> 상대 탱커 힐각 차단
    HealToTankDefense UMETA(DisplayName = "HealToTankDefense"),
};