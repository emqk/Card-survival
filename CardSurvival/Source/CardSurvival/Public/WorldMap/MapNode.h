// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/Interactable.h"
#include "MapNode.generated.h"

class AMapNodeConnection;

UCLASS()
class CARDSURVIVAL_API AMapNode : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AMapNode();

	// Interaction
	bool StartInteraction_Implementation(AActor* Interactor, EInteractionType InteractionType) override;
 
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;
};
