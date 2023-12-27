// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TBGMapTile.generated.h"

UENUM(BlueprintType)
enum class ETileType : uint8
{
	ETT_Default UMETA(DisplayName = "Default"),
	ETT_HighGround UMETA(DisplayName = "HighGround"),
	ETT_Blocked UMETA(DisplayName = "Blocked"),

	ETT_MAX UMETA(Hidden)
};

UCLASS()
class GD_TURNBASED_API ATBGMapTile : public AActor
{
	GENERATED_BODY()

public:
	ATBGMapTile();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mesh")
	TObjectPtr<UStaticMeshComponent> TileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETileType TileType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StepCost = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FIntVector Coordinates = FIntVector::ZeroValue;

	UFUNCTION(BlueprintNativeEvent)
	void SetTextRenderCoords(FIntVector Coords);

protected:
	virtual void BeginPlay() override;


};
