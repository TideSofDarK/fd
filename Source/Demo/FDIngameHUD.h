// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FDIngameHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AFDIngameHUD : public AHUD
{
	GENERATED_BODY()
	
	
public:
	/** SlideOutHUD */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HUD")
	void SlideOutHUD();
	
};
