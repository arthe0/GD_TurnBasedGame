// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TBGTileGrid.h"
#include "GameFramework/Actor.h"
#include "TBGMapTile.generated.h"

UENUM(BlueprintType)
enum class ETileType : uint8
{
	ETT_Default UMETA(DisplayName = "Default"),
	ETT_Spawn UMETA(DisplayName = "Spawn"),
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=TileSettings)
	ETileType TileType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=TileSettings)
	float StepCost = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=TileSettings)
	FIntVector Coordinates = FIntVector::ZeroValue;

	UFUNCTION(BlueprintNativeEvent)
	void SetTextRenderCoords(FIntVector Coords);

	UFUNCTION(BlueprintNativeEvent, CallInEditor, Category=TileSettings)
	void ApplyType();

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable)
	virtual void DestroyAllTileActors();

private:
	// Type change
	void SetSpawnType();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=TileSettings, meta=(AllowPrivateAccess = true))
	TArray<TObjectPtr<AActor>> TileActors;

	TObjectPtr<ATBGTileGrid> OwnerGrid;

public:
	UFUNCTION(BlueprintCallable)
	FVector GetCenterLocation() const;


};
