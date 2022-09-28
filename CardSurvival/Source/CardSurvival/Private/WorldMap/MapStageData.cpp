// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap/MapStageData.h"

UMapStageData::UMapStageData()
{

}

void UMapStageData::Generate(int NewHeight, int NewWidth, int NewStage, UMapNodeData* EnviroNodeData)
{
	Height = NewHeight;
	Width = NewWidth;
	Stage = NewStage;
	Data.Init(0, Width * Height);

	for (int X = 0; X < Height; X++)
	{
		for (int Y = 0; Y < Width; Y++)
		{
			Data[X * Width + Y] = EnviroNodeData;
		}
	}
}

UMapNodeData* UMapStageData::GetDataAt(int X, int Y) const
{
	int Index = X * Width + Y;
	if (!Data.IsValidIndex(Index))
	{
		return nullptr;
	}

	return Data[Index];
}

void UMapStageData::SetDataAt(int X, int Y, UMapNodeData* NewData)
{
	Data[X * Width + Y] = NewData;
}

void UMapStageData::AddPOI(int X, int Y, UMapNodeData* POIData)
{
	SetDataAt(X, Y, POIData);
	POIs.Add(FIntPoint(X, Y));
}
