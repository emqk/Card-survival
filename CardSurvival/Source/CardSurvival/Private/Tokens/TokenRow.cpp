// Fill out your copyright notice in the Description page of Project Settings.


#include "Tokens/TokenRow.h"
#include "Tokens/Token.h"
#include "Tokens/TokenData.h"

ATokenRow::ATokenRow()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ATokenRow::AddToken(UTokenData* Data)
{
	int Index = FindTokenIndexWithData(Data);
	int LocationIndex = Index < 0 ? TokenDatas.Num() : Index; // If index is < 0, find location based on the last index
	int TokenHeight = Index < 0 ? 0 : TokenDatas[Index].Tokens.Num();

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform Transform;
	Transform.SetLocation(FindLocationForToken(LocationIndex, TokenHeight));

	AToken* TokenInstance = Cast<AToken>(GetWorld()->SpawnActor(TokenClass, &Transform, Params));
	TokenInstance->SetInfoActive(false);
	TokenInstance->ApplyData(Data);

	if (Index < 0)
	{
		TokenDatas.Add(FTokenInstanceData{ Data, {TokenInstance} });
	}
	else
	{
		TokenDatas[Index].Tokens.Add(TokenInstance);
	}
}

void ATokenRow::RemoveToken(UTokenData* Data)
{
	int Index = FindTokenIndexWithData(Data);
	
	// Can't find the given data - return
	if (Index < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find token with name [%s]"), *Data->GetName().ToString())
		return;
	}

	// Destroy token actor and remove it from the array
	TokenDatas[Index].Tokens.Last()->Destroy();
	TokenDatas[Index].Tokens.RemoveAt(TokenDatas[Index].Tokens.Num() - 1);

	// If token data has been removed, refresh location of all tokens so new ones can fit
	if (TokenDatas[Index].Tokens.IsEmpty())
	{
		TokenDatas.RemoveAt(Index);
		RefreshTokensLocation();
	}
}

void ATokenRow::RefreshTokensLocation()
{
	for (int i = 0; i < TokenDatas.Num(); i++)
	{
		FTokenInstanceData& Data = TokenDatas[i];
		for (int j = 0; j < Data.Tokens.Num(); j++)
		{
			Data.Tokens[j]->SetActorLocation(FindLocationForToken(i, j));
		}
	}
}

int ATokenRow::FindTokenIndexWithData(const UTokenData* Data) const
{
	for (int i = 0; i < TokenDatas.Num(); i++)
	{
		const UTokenData* CurrData = TokenDatas[i].Data;
		if (CurrData == Data)
		{
			return i;
		}
	}

	return -1;
}

FVector ATokenRow::FindLocationForToken(int RowIndex, int TokenHeight)
{
	return FVector(GetLocationXFromIndex(RowIndex), GetActorLocation().Y, GetLocationZFromAmount(TokenHeight));
}

float ATokenRow::GetLocationXFromIndex(int Index) const
{
	return Index * SpacingX + GetActorLocation().X;
}

float ATokenRow::GetLocationZFromAmount(int Amount) const
{
	return Amount * SpacingZ + GetActorLocation().Z;
}

