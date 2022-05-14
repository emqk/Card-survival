// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interaction/Interactable.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARDSURVIVAL_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();

	void StartInteraction(IInteractable* Interactable);
	void TickInteraction();
	void EndInteraction();


	FHitResult GetResult();

protected:	

	UPROPERTY(EditDefaultsOnly)
	float InteractionDistance = 10000.0f;

	UPROPERTY(VisibleAnywhere)
	TScriptInterface<IInteractable> InteractableTarget = nullptr;
};
