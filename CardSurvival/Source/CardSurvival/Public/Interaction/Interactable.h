// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"


UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	Primary,
	Secondary,
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class CARDSURVIVAL_API IInteractable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool StartInteraction(AActor* Interactor, EInteractionType InteractionType);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool TickInteraction(AActor* Interactor);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool EndInteraction(AActor* Interactor);
};