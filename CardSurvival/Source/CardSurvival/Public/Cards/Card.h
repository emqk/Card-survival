// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/Interactable.h"
#include "Card.generated.h"

class UTextRenderComponent;
class UFollowComponent;
class APlayZone;
class UStatistic;

UCLASS()
class CARDSURVIVAL_API ACard : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ACard();

	void BeginPlay() override;

	// Interaction
	bool StartInteraction_Implementation(AActor* Interactor, EInteractionType InteractionType) override;
	bool TickInteraction_Implementation(AActor* Interactor) override;
	void OnTickInteractionEnd_Implementation(AActor* Interactor, bool TickEndResult) override;
	bool EndInteraction_Implementation(AActor* Interactor) override;

	// Select
	bool StartSelect_Implementation(AActor* Interactor) override;
	bool TickSelect_Implementation(AActor* Interactor) override;
	bool EndSelect_Implementation(AActor* Interactor) override;


	TObjectPtr<UFollowComponent> GetFollowComponent() const { return FollowComponent; };

	TObjectPtr<APlayZone> GetPlayZone() const { return PlayZone; };
	void SetPlayZone(TObjectPtr<APlayZone> NewPlayZone) { PlayZone = NewPlayZone; }


protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextRenderComponent> NameTextComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextRenderComponent> StrengthTextComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ProgressBarMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UFollowComponent> FollowComponent;

	UPROPERTY(EditDefaultsOnly, Instanced)
	TObjectPtr<UStatistic> Progress;
	// PlayZone in which this card is currently in
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<APlayZone> PlayZone;
	UPROPERTY(EditDefaultsOnly)
	FVector HoldHeightOffset = FVector(0, 0, 250);

	EInteractionType CurrentInteractionType;
};
