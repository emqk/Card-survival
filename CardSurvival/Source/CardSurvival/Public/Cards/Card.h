// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cards/CardBase.h"
#include "Interaction/Interactable.h"
#include "Card.generated.h"

class UTextRenderComponent;
class UWidgetComponent;
class UPlayerSubsystem;
class UCardData;
class ACardDummy;

UCLASS()
class CARDSURVIVAL_API ACard : public ACardBase, public IInteractable
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
	bool CanInteract_Implementation(EInteractionType InteractionType) override;

	// Select
	bool StartSelect_Implementation(AActor* Interactor) override;
	bool TickSelect_Implementation(AActor* Interactor) override;
	bool EndSelect_Implementation(AActor* Interactor) override;
	bool CanSelect_Implementation(AActor* Interactor) override;

	UFUNCTION(BlueprintCallable)
	void SetCardData(UCardData* NewCardData);
	UCardData* GetCardData() const { return CardData; };

	UPlayerSubsystem* GetPlayerSubsystem() const { return PlayerSubsystem; };
	void SetPlayerSubsystem();

protected:
	void ApplyCardData();
	void ApplyCardDataVisuals();

	void HighlightCard(bool Active);
	void HighlightBorder(bool Active);

	bool CanInteractAim();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> InfoWidgetComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ProgressBarMeshComponent;


	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCardData> CardData;

	UPROPERTY(VisibleAnywhere)
	float Progress = 0.0f;
	UPROPERTY(EditDefaultsOnly)
	float ProgressMax = 3.8f;

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
	float InteractionStartTime = 0.0f;
	const float InteractionAimTimeThreshold = 0.2f;
	TObjectPtr<ACardDummy> CardDummy = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPlayerSubsystem> PlayerSubsystem;

};
