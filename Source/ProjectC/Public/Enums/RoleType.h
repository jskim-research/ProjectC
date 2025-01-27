#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ERoleType : uint8
{
    None UMETA(DisplayName = "None"),
    Tank UMETA(DisplayName = "Tank"),
    Healer UMETA(DisplayName = "Healer"),
    Dealer UMETA(DisplayName = "Dealer")
};