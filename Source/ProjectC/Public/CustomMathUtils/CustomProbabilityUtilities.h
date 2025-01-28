#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetMathLibrary.h"

struct FCustomProbabilityUtilities
{
	static FORCEINLINE bool IsProbabilitySuccessful(int32 Percentage)
	{
		Percentage = FMath::Clamp(Percentage, 0, 100);
		int32 RandomValue = FMath::RandRange(0, 99);

		if (RandomValue < Percentage)
			return true;

		return false;
	}

	static FORCEINLINE FVector GenerateRandomSphericalPoint()
	{
		FVector RandomEvasionPoint = FVector::ZeroVector;
		float Angle = FMath::FRand() * 2.0f * PI;
		// 제곱근 분포로 원형의 원점에 밀도가 높은 현상 보정 => 밀도 uniform 하게
		float Radius = FMath::Sqrt(FMath::FRand()) * 300;

		RandomEvasionPoint.X = Radius * FMath::Cos(Angle);
		RandomEvasionPoint.Y = Radius * FMath::Sin(Angle);

		return RandomEvasionPoint;
	}
};