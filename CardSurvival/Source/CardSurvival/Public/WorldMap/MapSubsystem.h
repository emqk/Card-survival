// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MapSubsystem.generated.h"

class AMapNode;

USTRUCT(BlueprintType)
struct FMapLevelData
{
	GENERATED_BODY();

public:
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<AMapNode>> Nodes;
};


UCLASS(Blueprintable, Abstract)
class CARDSURVIVAL_API UMapSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	// Overrides - GameInstanceSubsystem
	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;

	UFUNCTION(BlueprintImplementableEvent)
	void BlueprintInitialize();


	UFUNCTION(BlueprintCallable)
	void CreateNewLevel();
	UFUNCTION(BlueprintCallable)
	AMapNode* SpawnNode(const FVector& Location);

protected:
	FVector FindLevelLocationByIndex(int32 LevelIndex);

protected:

	UPROPERTY(VisibleAnywhere)
	TArray<FMapLevelData> Levels;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMapNode> MapNodeClass;
	UPROPERTY(EditDefaultsOnly)
	FVector MapLevelStartLocation = {10000, 0, 0};
	UPROPERTY(EditDefaultsOnly)
	FVector2D LevelSize = {2000, 1000};
	UPROPERTY(EditDefaultsOnly)
	float NodeSize = 100;
	UPROPERTY(EditDefaultsOnly)
	FIntPoint NodesInLevelRange = {2, 5};
};
