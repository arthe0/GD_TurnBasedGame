// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "TBGPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class GD_TURNBASED_API ATBGPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 SpawnIndex = 0;

};
