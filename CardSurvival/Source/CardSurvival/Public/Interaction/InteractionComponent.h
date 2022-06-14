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

	// Interaction
	void StartInteraction(IInteractable* Interactable, EInteractionType InteractionType);
	void TickInteraction();
	void EndInteraction();

	// Select
	void StartSelect(IInteractable* Interactable);
	void TickSelect();
	void EndSelect();

	FHitResult GetResult();

	bool IsActorSelected(AActor* Actor) const;

protected:	

	UPROPERTY(EditDefaultsOnly)
	float InteractionDistance = 10000.0f;

	UPROPERTY(VisibleAnywhere)
	TScriptInterface<IInteractable> InteractableTarget = nullptr;
	UPROPERTY(VisibleAnywhere)
	TScriptInterface<IInteractable> SelectTarget = nullptr;
};
