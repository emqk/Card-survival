// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EventChoiceWidget.generated.h"

class UEventAction;

UCLASS()
class CARDSURVIVAL_API UEventChoiceWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetActionClass(const TSubclassOf<UEventAction>& NewActionClass) { ActionClass = NewActionClass; };


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<UEventAction> ActionClass;
};