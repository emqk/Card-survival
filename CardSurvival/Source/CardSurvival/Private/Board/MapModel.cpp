// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/MapModel.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerSubsystem.h"
#include "Player/PlayerMapPawn.h"

AMapModel::AMapModel()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);
}

bool AMapModel::StartInteraction_Implementation(AActor* Interactor, EInteractionType InteractionType)
{
	UE_LOG(LogTemp, Warning, TEXT("Interacted with the map"))
		
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APlayerMapPawn* PlayerPawn = GetGameInstance()->GetSubsystem<UPlayerSubsystem>()->GetPlayerMapPawn();
	
	PlayerController->Possess(PlayerPawn);

	return true;
}

bool AMapModel::EndInteraction_Implementation(AActor* Interactor)
{
	UE_LOG(LogTemp, Warning, TEXT("Interacted with the map ended"))

	return true;
}

