// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OwnPlayerController.generated.h"

class APlayerPawn;
class ACursor;

UCLASS()
class CARDSURVIVAL_API AOwnPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	AOwnPlayerController();

	void BeginPlay() override;
	void PlayerTick(float DeltaTime) override;

	TObjectPtr<ACursor> GetCursor3D() const { return Cursor3D; };

protected:
	void OnPossess(APawn* aPawn) override;
	void SetupInputComponent() override;

private:
	void PrimaryInputPressed();
	void PrimaryInputReleased();
	void SecondaryInputPressed();
	void SecondaryInputReleased();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<APlayerPawn> PlayerPawn;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ACursor> Cursor3D;

};
