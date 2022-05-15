// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

// Own
#include "PlayerPawn.generated.h"

class UCameraComponent;
class UInteractionComponent;
class UFollowComponent;
class ACursor;

UCLASS()
class CARDSURVIVAL_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	const FHitResult& GetHitResult() const { return HitResult; };
	ACursor* GetCursor3D() const;


private:
	
	void PrimaryInputPressed();
	void PrimaryInputReleased();


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInteractionComponent* InteractionComponent;

	
	// Cached interaction hit actor
	UPROPERTY();
	AActor* HitActor = nullptr;
	UPROPERTY();
	FHitResult HitResult;

	UPROPERTY(VisibleAnywhere)
	ACursor* Cursor3D;
};
