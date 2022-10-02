// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interaction/Interactable.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class AInteractionAim;
class ACardBase;

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
	bool IsInteracting() const;

	// Aim
	void TickAim();
	bool IsAiming() const { return InteractionAimInstance != nullptr; }
	AActor* GetAimStart() const;
	AInteractionAim* GetInteractionAim(AActor* Start);
	void DestroyInteractionAim();

protected:	

	UPROPERTY(EditDefaultsOnly)
	float InteractionDistance = 10000.0f;

	UPROPERTY(VisibleAnywhere)
	TScriptInterface<IInteractable> InteractableTarget = nullptr;
	UPROPERTY(VisibleAnywhere)
	TScriptInterface<IInteractable> SelectTarget = nullptr;

	// Aim
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AInteractionAim> InteractionAimClass;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AInteractionAim> InteractionAimInstance;
};
