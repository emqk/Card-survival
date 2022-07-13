// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapStageData.generated.h"

USTRUCT(BlueprintType)
struct CARDSURVIVAL_API FMapStageData
{

	GENERATED_BODY()

public:
	void Generate(int NewHeight, int NewWidth, int NewStage);
	int GetDataAt(int X, int Y) const;
	void SetDataAt(int X, int Y, int NewData);

	void AddPOI(int X, int Y);
	const TArray<FIntPoint>& GetPOIs() const { return POIs; };

	int GetStage() const { return Stage; };

protected:
	int Height;
	int Width;

	TArray<int> Data;
	TArray<FIntPoint> POIs;
	int Stage = -1;
};
