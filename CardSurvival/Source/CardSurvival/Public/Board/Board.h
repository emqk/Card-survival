// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

class UPlayZoneComponent;

UCLASS()
class CARDSURVIVAL_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoard();


protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BoardMesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPlayZoneComponent> PlayerEQPlayZone;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPlayZoneComponent> PlayerInventoryPlayZone;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPlayZoneComponent> LocationPlayZone;
};
