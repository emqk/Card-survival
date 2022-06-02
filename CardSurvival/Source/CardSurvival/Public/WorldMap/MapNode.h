// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapNode.generated.h"

class AMapNodeConnection;

UCLASS()
class CARDSURVIVAL_API AMapNode : public AActor
{
	GENERATED_BODY()
	
public:	
	AMapNode();

	void AddConnection(AMapNode* Node);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<AMapNode>> Connections;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AMapNodeConnection> ConnectionClass;
};
