// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TBGTileGrid.generated.h"

class ATBGMapTile;

UCLASS()
class GD_TURNBASED_API ATBGTileGrid : public AActor
{
	GENERATED_BODY()

public:
	ATBGTileGrid();

	UFUNCTION(BlueprintNativeEvent, CallInEditor, Category=Generation)
	void ReGenerateGrid();

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable)
	virtual void GenerateBaseGrid(FIntVector Dimensions);

	UFUNCTION(BlueprintCallable)
	virtual void DestroyAllTiles();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Generation)
	TSubclassOf<ATBGMapTile> TileClass;

private:
	// Map generation
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Generation, meta=(AllowPrivateAccess = true))
	float TileOuterRadius = 200.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Generation, meta=(AllowPrivateAccess = true))
	float TileInnerRadius = 0.f; // Calculated depending on Outer Radius

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Generation, meta=(AllowPrivateAccess = true))
	float TileScale = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Generation, meta=(AllowPrivateAccess = true))
	FRotator TileRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Generation, meta=(AllowPrivateAccess = true))
	FIntVector GridDimensions = FIntVector(5, 5, 5);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Generation, meta=(AllowPrivateAccess = true))
	TMap<FIntVector, TObjectPtr<ATBGMapTile>> MapTiles;

	// Helper functions
	static float CalculateTileInnerRadius(float OuterRadius);

public:
	// Getters and Setters

	UFUNCTION(BlueprintCallable)
	ATBGMapTile* GetTileAtCoordinates(const int32 X, const int32 Y, const int32 Z);

	UFUNCTION(BlueprintCallable)
	ATBGMapTile* GetTileAtCoordinatesVector(const FIntVector Coordinates);
};
