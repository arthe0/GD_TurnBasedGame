// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Map/TBGTileGrid.h"

#include "Core/Map/TBGMapTile.h"

DEFINE_LOG_CATEGORY_STATIC(Log_TBGMapGrid, Log, All);

ATBGTileGrid::ATBGTileGrid()
{
	TileInnerRadius = CalculateTileInnerRadius(TileOuterRadius);
	PrimaryActorTick.bCanEverTick = false;
}

void ATBGTileGrid::ReGenerateGrid_Implementation()
{
	Destroy();
	GenerateBaseGrid(GridDimensions);
}

void ATBGTileGrid::BeginPlay() { Super::BeginPlay(); }

void ATBGTileGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	TileInnerRadius = CalculateTileInnerRadius(TileOuterRadius);
}

// Map generation
void ATBGTileGrid::GenerateBaseGrid(const FIntVector Dimensions)
{
	if (Dimensions.X < 1 || Dimensions.Y < 1 || Dimensions.Z < 1)
	{
		UE_LOG(Log_TBGMapGrid, Error, TEXT("Unable to generate grid with one of dimension less than 0 with: %s"),
			*Dimensions.ToString());
		return;
	}

	UWorld* World = GetWorld();
	if (!World) { return; }

	for (int32 X = -Dimensions.X; X <= Dimensions.X; ++X)
	{
		for (int32 Y = -Dimensions.Y; Y <= Dimensions.Y; ++Y)
		{
			for (int32 Z = -Dimensions.Z; Z <= Dimensions.Z; ++Z)
			{
				if (X + Y + Z != 0) { continue; }

				FActorSpawnParameters SpawnParameters;
				FVector               Location;

				float XSign = FMath::Sign(Z);
				if (Y > 0 && X < Z) { XSign = 1; }
				else if (Y > 0 && X > Z) { XSign = -1; }
				else if (Y < 0 && X < Z) { XSign = 1; }
				else
					if (Y < 0 && X > Z) { XSign = -1; }

				float XOffsetSteps = FMath::Abs(X) + FMath::Abs(Z);
				if ((X < 0 && Z < 0) || X > 0 && Z > 0) { XOffsetSteps = FMath::Abs(FMath::Abs(X) - FMath::Abs(Z)); }

				const float WorldXOffset = TileInnerRadius * XSign * XOffsetSteps;
				const float WorldYOffset = (TileOuterRadius + TileOuterRadius / 2) * Y;

				Location.X = WorldXOffset * TileScale;
				Location.Y = WorldYOffset * TileScale;
				Location.Z = GetActorLocation().Z;
				const TObjectPtr<ATBGMapTile> Tile = World->SpawnActorDeferred<ATBGMapTile>(TileClass, GetActorTransform());
				if (!Tile)
				{
					UE_LOG(Log_TBGMapGrid, Error, TEXT("TILE IS MISSING"));
					continue;
				}
				Tile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				Tile->SetActorRelativeLocation(Location);

				const FIntVector TileCoords = FIntVector(X, Y, Z);
				MapTiles.Add(TileCoords, Tile);
				Tile->Coordinates = TileCoords;
				Tile->FinishSpawning(Tile->GetActorTransform());

				Tile->SetActorRelativeScale3D(FVector(TileScale));
				Tile->SetActorRotation(TileRotation);
				Tile->SetTextRenderCoords(TileCoords);
			}
		}
	}

}

void ATBGTileGrid::Destroy()
{
	if (MapTiles.IsEmpty()) { return; }
	for (const auto& Tile : MapTiles) { Tile.Value->Destroy(); }

	MapTiles.Reset();
}

// Helper functions
float ATBGTileGrid::CalculateTileInnerRadius(const float OuterRadius) { return OuterRadius * FMath::Sqrt(3.f) / 2; }
