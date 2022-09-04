// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/Interactable.h"
#include "Card.generated.h"

class UTextRenderComponent;
class UWidgetComponent;
class UFollowComponent;
class UPlayerSubsystem;
class UPlayZoneComponent;
class UCardData;

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

	UFUNCTION(BlueprintCallable)
	void SetCardData(UCardData* NewCardData);

	TObjectPtr<UFollowComponent> GetFollowComponent() const { return FollowComponent; };

	TObjectPtr<UPlayZoneComponent> GetPlayZone() const { return PlayZone; };
	void SetPlayZone(TObjectPtr<UPlayZoneComponent> NewPlayZone) { PlayZone = NewPlayZone; }

	UPlayerSubsystem* GetPlayerSubsystem() const { return PlayerSubsystem; };
	void SetPlayerSubsystem();

protected:
	void ApplyCardData();
	void ApplyCardDataVisuals();

	void HighlightCard(bool Active);
	void HighlightBorder(bool Active);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> InfoWidgetComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ProgressBarMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UFollowComponent> FollowComponent;


	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCardData> CardData;

	UPROPERTY(VisibleAnywhere)
	float Progress = 0.0f;
	UPROPERTY(EditDefaultsOnly)
	float ProgressMax = 3.8f;

	// PlayZone in which this card is currently in
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPlayZoneComponent> PlayZone;
	UPROPERTY(EditDefaultsOnly)
	FVector HoldHeightOffset = FVector(0, 0, 250);

	UPROPERTY(EditDefaultsOnly)
	float EmissionStrengthSelect = 40.0f;
	UPROPERTY(EditDefaultsOnly)
	float EmissionStrengthDefault = 1.0f;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> BorderDynamicMaterialInstance = nullptr;
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> BackgroundDynamicMaterialInstance = nullptr;
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> ItemTextureMaterialInstance = nullptr;

	EInteractionType CurrentInteractionType;


	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPlayerSubsystem> PlayerSubsystem;
};
