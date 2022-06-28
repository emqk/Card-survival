// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/Interactable.h"
#include "Token.generated.h"

class UWidgetComponent;
class UFollowComponent;
class ATokenData;
class UTokenStack;

UCLASS()
class CARDSURVIVAL_API AToken : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AToken();

	// Select
	bool StartSelect_Implementation(AActor* Interactor) override;
	bool EndSelect_Implementation(AActor* Interactor) override;


	UFUNCTION(BlueprintCallable)
	void ApplyData(UTokenData* Data);
	UFUNCTION(BlueprintCallable)
	void SetInfoActive(bool Active);

	void SetTokenStack(UTokenStack* Stack) { MyTokenStack = Stack; };
	UTokenStack* GetMyTokenStack() const { return MyTokenStack; };

	void SetDefaultWorldLocation(const FVector& NewLocation) { DefaultWorldLocation = NewLocation; };
	FVector GetDefaultWorldLocation() const { return DefaultWorldLocation; };

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
	UPROPERTY(VisibleAnywhere)
	FVector DefaultWorldLocation;
	UPROPERTY(VisibleAnywhere)
	UTokenStack* MyTokenStack;
};
