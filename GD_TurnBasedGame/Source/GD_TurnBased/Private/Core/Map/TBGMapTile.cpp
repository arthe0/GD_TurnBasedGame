// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Map/TBGMapTile.h"
#include "GameFramework/Actor.h"
#include "Core/Map/TBGTileGrid.h"

#include "Core/Map/TBGPlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ATBGMapTile::ATBGMapTile()
{
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>("Tile Mesh");
	SetRootComponent(TileMesh);

	TileType = ETileType::ETT_Default;

	PrimaryActorTick.bCanEverTick = false;
}

void ATBGMapTile::BeginPlay() { Super::BeginPlay(); }

void ATBGMapTile::BeginDestroy()
{
	Super::BeginDestroy();

	DestroyAllTileActors();
}

void ATBGMapTile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ATBGTileGrid* TileOwnerGrid = GetOwner<ATBGTileGrid>();
	if (TileOwnerGrid) { OwnerGrid = TileOwnerGrid; }
}

void ATBGMapTile::ApplyType_Implementation()
{
	DestroyAllTileActors();

	switch (TileType)
	{
		case ETileType::ETT_Default:
			break;

		case ETileType::ETT_Spawn:
			SetSpawnType();
			break;

		case ETileType::ETT_Blocked:
			break;

		case ETileType::ETT_HighGround:
			break;
	}
}

void ATBGMapTile::DestroyAllTileActors()
{
	if (!TileActors.IsEmpty()) { return; }

	for (const auto Actor : TileActors) { Actor->Destroy(); }
	TileActors = TArray<TObjectPtr<AActor>>();
}

void ATBGMapTile::SetSpawnType()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (!World) { return; }

	const TObjectPtr<ATBGPlayerStart> PlayerStart = World->SpawnActor<ATBGPlayerStart>(ATBGPlayerStart::StaticClass(), GetActorTransform());
	if (!PlayerStart) { return; }
	TileActors.Add(*PlayerStart);

	FVector Location = GetCenterLocation();
	Location.Z += 100.f;
	PlayerStart->SetActorLocation(Location);

	const ATBGMapTile* CenterTile = OwnerGrid->GetTileAtCoordinates(0, 0, 0);
	if (CenterTile)
	{
		const FRotator RotationToCenter = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CenterTile->GetActorLocation());
		PlayerStart->SetActorRotation(RotationToCenter);
	}

}

void ATBGMapTile::SetTextRenderCoords_Implementation(FIntVector Coords) {}

FVector ATBGMapTile::GetCenterLocation() const { return TileMesh->GetSocketLocation("MeshCenter"); }
