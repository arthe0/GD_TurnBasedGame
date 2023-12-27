// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Map/TBGMapTile.h"

ATBGMapTile::ATBGMapTile()
{
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>("Tile Mesh");
	SetRootComponent(TileMesh);

	TileType = ETileType::ETT_Default;

	PrimaryActorTick.bCanEverTick = false;
}

void ATBGMapTile::BeginPlay() { Super::BeginPlay(); }

void ATBGMapTile::SetTextRenderCoords_Implementation(FIntVector Coords) {}
