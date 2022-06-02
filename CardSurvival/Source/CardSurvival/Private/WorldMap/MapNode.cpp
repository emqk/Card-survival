// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap/MapNode.h"
#include "WorldMap/MapNodeConnection.h"

AMapNode::AMapNode()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);
}

void AMapNode::AddConnection(AMapNode* Node)
{
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform Transform;

	AMapNodeConnection* ConnectionActor = Cast<AMapNodeConnection>(GetWorld()->SpawnActor(ConnectionClass, &Transform, Params));
	ConnectionActor->SetConnectionData(this, Node);
	Connections.Add(Node);
}
