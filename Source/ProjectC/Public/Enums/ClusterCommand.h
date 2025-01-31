#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EClusterCommand : uint8
{
    None UMETA(DisplayName = "None"),
    // 전선 유지
    Hold UMETA(DisplayName = "Hold"),
    // 돌진
    Charge UMETA(DisplayName = "Charge"),
};