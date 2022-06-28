// Fill out your copyright notice in the Description page of Project Settings.


#include "Tokens/TokenStack.h"

bool UTokenStack::IsTokenOnTop(AToken* Token)
{
	if (Token == nullptr || Tokens.Num() <= 0)
	{
		return false;
	}

	return Tokens.Last() == Token;
}
