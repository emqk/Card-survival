// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/Board.h"
#include "Board/PlayZoneComponent.h"
#include "Player/PlayerSubsystem.h"

ABoard::ABoard()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	// Mesh
	BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BoardMesh->SetupAttachment(RootComponent);

	// Play Zones
	PlayerEQPlayZone = CreateDefaultSubobject<UPlayZoneComponent>(TEXT("EQPlayZone"));
	PlayerEQPlayZone->SetCollisionProfileName(TEXT("BlockAll"));
	PlayerEQPlayZone->SetupAttachment(RootComponent);

	PlayerInventoryPlayZone = CreateDefaultSubobject<UPlayZoneComponent>(TEXT("PlayerInventoryPlayZone"));
	PlayerInventoryPlayZone->SetCollisionProfileName(TEXT("BlockAll"));
	PlayerInventoryPlayZone->SetupAttachment(RootComponent);

	LocationPlayZone = CreateDefaultSubobject<UPlayZoneComponent>(TEXT("LocationPlayZone"));
	LocationPlayZone->SetCollisionProfileName(TEXT("BlockAll"));
	LocationPlayZone->SetupAttachment(RootComponent);
}

void ABoard::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetSubsystem<UPlayerSubsystem>()->SetBoard(this);
}

UPlayZoneComponent* ABoard::GetPlayZoneFromLocation(const FVector2D& Location2D) const
{
	if (PlayerEQPlayZone->IsLocationInPlayZone(Location2D))
	{
		return PlayerEQPlayZone;
	}
	else if (PlayerInventoryPlayZone->IsLocationInPlayZone(Location2D))
	{
		return PlayerInventoryPlayZone;
	}
	else if (LocationPlayZone->IsLocationInPlayZone(Location2D))
	{
		return LocationPlayZone;
	}

	return nullptr;
}
