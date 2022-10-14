// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/PlayerPawn.h"
#include "PlayerMapPawn.generated.h"

class UFollowComponent;
class UWorldMapStatsWidget;

UCLASS()
class CARDSURVIVAL_API APlayerMapPawn : public APlayerPawn
{
	GENERATED_BODY()
	
public:	
	APlayerMapPawn();

	virtual void BeginPlay() override;

	void MoveToWorldIndex(const FIntPoint& NewLocation);
	void MoveToWorldIndex_Instant(const FIntPoint& NewLocation);

	FIntPoint GetWorldIndex() const { return WorldLocationIndex; };

	void SetStatsActive(bool bActive);
	UFUNCTION(BlueprintImplementableEvent)
	void RefreshStats();

	UFUNCTION(BlueprintPure)
	int32 GetEnergyDecreaseAfterStep() const { return EnergyDecreaseAfterStep; }

protected:
	void SpawnNodesInView();

protected:
	UPROPERTY(EditDefaultsOnly)
	int32 ViewDistance = 2;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UFollowComponent> FollowComponent;


	UPROPERTY(EditDefaultsOnly)
	FVector WalkOffset = FVector(0, 0, 100);
	UPROPERTY(VisibleAnywhere)
	FIntPoint WorldLocationIndex;

	UPROPERTY(EditDefaultsOnly)
	int32 EnergyDecreaseAfterStep = -4;

	// UI
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UWorldMapStatsWidget> WorldMapStatsWidgetClass;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UWorldMapStatsWidget> WorldMapStatsWidgetInstance;
};
