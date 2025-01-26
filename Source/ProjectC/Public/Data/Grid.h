#pragma once
#include "CoreMinimal.h"
#include "Enums/RoleType.h"
#include "Grid.generated.h"


USTRUCT(BlueprintType)
struct FGridTile
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
    ERoleType RoleType = ERoleType::None;  // Tank, Healer, Dealer
    bool IsAlly = false; 
    
    FGridTile()
    {

    }

    FGridTile(ERoleType InRoleType, bool InIsAlly)
    {
        RoleType = InRoleType;
        IsAlly = InIsAlly;
    }
};

USTRUCT(BlueprintType)
struct FGrid
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
    TArray<FGridTile> GridArray;

    int RowSize = 0;
    int ColSize = 0;

    FGrid()
    {

    }

    FGrid(int InRowSize, int InColSize)
    {
        InitGrid(InRowSize, InColSize);
    }

    void InitGrid(int InRowSize, int InColSize)
    {
        if (InRowSize < 0 || InColSize < 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("FGrid: Size of row or column should be bigger than zero."));
        }

        RowSize = InRowSize;
        ColSize = InColSize;

        // RowSize * ColumnSize 배열 생성
        GridArray.SetNum(RowSize * ColSize);
    }

    FGridTile& operator()(int RowIndex, int ColumnIndex)
    {    
        // 비상수 함수에서 상수 함수를 활용함으로써 코드 길이를 줄이고자 함
        return const_cast<FGridTile&>(static_cast<const FGrid&>(*this)(RowIndex, ColumnIndex));
    }

    const FGridTile& operator()(int RowIndex, int ColumnIndex) const
    {
        if (RowIndex < 0 || RowIndex >= RowSize || ColumnIndex < 0 || ColumnIndex >= ColSize)
        {
            UE_LOG(LogTemp, Warning, TEXT("FGrid: Index out of bound."));
        }
        return GridArray[RowIndex * RowSize + ColumnIndex];
    }
};