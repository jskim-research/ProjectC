#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetMathLibrary.h"
#include <array>

struct FCustomClusterUtilities
{
    // TEnableIf<true>::Type -> valid
    // TEnableIf<false>::Type -> invalid (template deleted)
    template <typename T, typename = typename TEnableIf<TIsDerivedFrom<T, AActor>::Value>::Type>
    static FORCEINLINE FVector CalculateAverageLocation(const TArray<T*>& Array)
    {
        if (Array.Num() == 0)
        {
            return FVector::ZeroVector;
        }

        FVector SumLocation = FVector::ZeroVector;
        for (const T* Actor : Array)
        {
            if (Actor) // nullptr 체크
            {
                SumLocation += Actor->GetActorLocation();
            }
        }

        return SumLocation / Array.Num();
    }

    template <typename T, int32 N, typename = typename TEnableIf<TIsDerivedFrom<T, AActor>::Value>::Type>
    static FORCEINLINE FVector CalculateAverageLocation(const std::array<TArrayView<T *const>, N>& Views)
    {
        FVector SumLocation = FVector::ZeroVector;
        int32 ActorNum = 0;
        for (const TArrayView<T *const>& View : Views)
        {
            for (AActor* Actor : View)
            {
                if (Actor)
                {
                    ActorNum++;
                    SumLocation += Actor->GetActorLocation();
                }
            }
        }

        if (ActorNum == 0)
        {
            return FVector::ZeroVector;
        }

        return SumLocation / ActorNum;
    }
};