// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap/MapNodeConnection.h"
#include "WorldMap/MapNode.h"


AMapNodeConnection::AMapNodeConnection()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);
}

void AMapNodeConnection::BeginPlay()
{
	Super::BeginPlay();

	ConnectTo();
}

void AMapNodeConnection::SetConnectionData(AMapNode* StartNode, AMapNode* EndNode)
{
	From = StartNode;
	To = EndNode;
}