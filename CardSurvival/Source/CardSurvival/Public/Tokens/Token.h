// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Token.generated.h"

class UWidgetComponent;
class UFollowComponent;
class ATokenData;

UCLASS()
class CARDSURVIVAL_API AToken : public AActor
{
	GENERATED_BODY()
	
public:	
	AToken();

	UFUNCTION(BlueprintCallable)
	void ApplyData(UTokenData* Data);
	UFUNCTION(BlueprintCallable)
	void SetInfoActive(bool Active);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> TokenMeshComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> TextBackgroundComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> InfoWidgetComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UFollowComponent> FollowComponent;

	UPROPERTY(VisibleAnywhere)
	bool bIsInfoActive = false;
};
