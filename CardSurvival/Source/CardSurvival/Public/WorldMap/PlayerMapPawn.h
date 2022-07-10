// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/PlayerPawn.h"
#include "PlayerMapPawn.generated.h"

class UFollowComponent;

UCLASS()
class CARDSURVIVAL_API APlayerMapPawn : public APlayerPawn
{
	GENERATED_BODY()
	
public:	
	APlayerMapPawn();

	void BeginPlay() override;

	void MoveToWorldIndex(const FIntPoint& NewLocation);
	void MoveToWorldIndex_Instant(const FIntPoint& NewLocation);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UFollowComponent> FollowComponent;


	UPROPERTY(EditDefaultsOnly)
	FVector WalkOffset = FVector(0, 0, 100);
	UPROPERTY(VisibleAnywhere)
	FIntPoint WorldLocationIndex;

};
