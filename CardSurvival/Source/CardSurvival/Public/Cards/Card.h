// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/Interactable.h"
#include "Card.generated.h"

class UTextRenderComponent;
class UFollowComponent;
class APlayZone;

UCLASS()
class CARDSURVIVAL_API ACard : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ACard();

	bool StartInteraction_Implementation(AActor* Interactor) override;
	bool TickInteraction_Implementation(AActor* Interactor) override;
	bool EndInteraction_Implementation(AActor* Interactor) override;

	UFollowComponent* GetFollowComponent() const { return FollowComponent; };

	APlayZone* GetPlayZone() const { return PlayZone; };
	void SetPlayZone(APlayZone* NewPlayZone) { PlayZone = NewPlayZone; }


protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UTextRenderComponent* NameTextComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UFollowComponent* FollowComponent;


	// PlayZone in which this card is currently in
	UPROPERTY(VisibleAnywhere)
	APlayZone* PlayZone;
	UPROPERTY(EditDefaultsOnly)
	FVector HoldHeightOffset = FVector(0, 0, 250);
};
