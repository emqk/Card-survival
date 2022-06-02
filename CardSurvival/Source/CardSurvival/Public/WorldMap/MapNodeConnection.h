// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapNodeConnection.generated.h"

class AMapNode;

UCLASS()
class CARDSURVIVAL_API AMapNodeConnection : public AActor
{
	GENERATED_BODY()
	
public:	
	AMapNodeConnection();

	void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ConnectTo();

	void SetConnectionData(AMapNode* StartNode, AMapNode* EndNode);


protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<AMapNode> From;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<AMapNode> To;
};
