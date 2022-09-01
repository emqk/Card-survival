// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StatisticBoard.generated.h"

UCLASS()
class CARDSURVIVAL_API AStatisticBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	AStatisticBoard();

protected:
	UFUNCTION(BlueprintPure)
	float GetMaxBarScale() const { return MaxBarScale; };


protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> HealthBarComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> EnergyBarComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> SanityBarComponent;


	UPROPERTY(EditDefaultsOnly)
	float MaxBarScale = 6.35f;
};
