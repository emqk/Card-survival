// Fill out your copyright notice in the Description page of Project Settings.


#include "Tokens/TokenRow.h"
#include "Tokens/Token.h"
#include "Tokens/TokenData.h"
#include "Tokens/TokenStack.h"

ATokenRow::ATokenRow()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ATokenRow::AddTokens(UTokenData* Data, int32 Amount)
{
	for (int i = 0; i < Amount; i++)
	{
		AddToken(Data);
	}
}

void ATokenRow::AddToken(UTokenData* Data)
{
	if (!Data)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't add token - Data is null!"))
		return;
	}

	int Index = FindTokenIndexWithData(Data);
	int LocationIndex = Index < 0 ? TokenStacks.Num() : Index; // If index is < 0, find location based on the last index
	int TokenHeight = Index < 0 ? 0 : TokenStacks[Index]->Tokens.Num();

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform Transform;
	Transform.SetLocation(FindLocationForToken(LocationIndex, TokenHeight));

	AToken* TokenInstance = Cast<AToken>(GetWorld()->SpawnActor(TokenClass, &Transform, Params));
	TokenInstance->SetInfoActive(false);
	TokenInstance->ApplyData(Data);
	TokenInstance->SetDefaultWorldLocation(Transform.GetLocation());

	if (Index < 0)
	{
		UTokenStack* NewTokenStack = NewObject<UTokenStack>(this);
		NewTokenStack->Data = Data;
		NewTokenStack->Tokens = { TokenInstance };
		TokenInstance->SetTokenStack(NewTokenStack);

		TokenStacks.Add(NewTokenStack);
	}
	else
	{
		TokenInstance->SetTokenStack(TokenStacks[Index]);
		TokenStacks[Index]->Tokens.Add(TokenInstance);
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
	TokenStacks[Index]->Tokens.Last()->Destroy();
	TokenStacks[Index]->Tokens.RemoveAt(TokenStacks[Index]->Tokens.Num() - 1);

	// If token data has been removed, refresh location of all tokens so new ones can fit
	if (TokenStacks[Index]->Tokens.IsEmpty())
	{
		TokenStacks.RemoveAt(Index);
		RefreshTokensLocation();
	}
}

void ATokenRow::RefreshTokensLocation()
{
	for (int i = 0; i < TokenStacks.Num(); i++)
	{
		UTokenStack* Data = TokenStacks[i];
		for (int j = 0; j < Data->Tokens.Num(); j++)
		{
			FVector NewLocation = FindLocationForToken(i, j);
			Data->Tokens[j]->SetActorLocation(NewLocation);
			Data->Tokens[j]->SetDefaultWorldLocation(NewLocation);
		}
	}
}

int ATokenRow::FindTokenIndexWithData(const UTokenData* Data) const
{
	for (int i = 0; i < TokenStacks.Num(); i++)
	{
		const UTokenData* CurrData = TokenStacks[i]->Data;
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

