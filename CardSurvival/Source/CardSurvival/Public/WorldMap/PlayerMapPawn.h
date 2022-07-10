// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerMapPawn.generated.h"

class UFollowComponent;

UCLASS()
class CARDSURVIVAL_API APlayerMapPawn : public AActor
{
	GENERATED_BODY()
	
public:	
	APlayerMapPawn();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UFollowComponent> FollowComponent;
};
