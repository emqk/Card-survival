// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap/MapStageData.h"
#include "Kismet/KismetMathLibrary.h"

void FMapStageData::Generate(int NewHeight, int NewWidth, int NewStage)
{
	Height = NewHeight;
	Width = NewWidth;
	Stage = NewStage;
	Data.Init(0, Width * Height);

	for (int X = 0; X < Height; X++)
	{
		for (int Y = 0; Y < Width; Y++)
		{
			Data[X * Width + Y] = UKismetMathLibrary::RandomIntegerInRange(0, 0);
		}
	}
}

int FMapStageData::GetDataAt(int X, int Y) const
{
	return Data[X * Width + Y];
}

void FMapStageData::SetDataAt(int X, int Y, int NewData)
{
	Data[X * Width + Y] = NewData;
}

void FMapStageData::AddPOI(int X, int Y)
{
	SetDataAt(X, Y, 1);
	POIs.Add(FIntPoint(X, Y));
}
