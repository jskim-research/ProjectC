#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ERoleType : uint8
{
    None UMETA(DisplayName = "None"),
    Tank UMETA(DisplayName = "Intro"),
    Healer UMETA(DisplayName = "Combat"),
    Dealer UMETA(DisplayName = "Victory")
};