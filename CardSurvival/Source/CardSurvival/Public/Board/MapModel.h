// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/Interactable.h"
#include "MapModel.generated.h"

UCLASS()
class CARDSURVIVAL_API AMapModel : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AMapModel();

	// Interaction
	bool StartInteraction_Implementation(AActor* Interactor, EInteractionType InteractionType) override;
	bool EndInteraction_Implementation(AActor* Interactor) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

};
