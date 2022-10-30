// Fill out your copyright notice in the Description page of Project Settings.


#include "HallwaySegment.h"

#include "KismetProceduralMeshLibrary.h"

// Sets default values
AHallwaySegment::AHallwaySegment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("Mesh Component");
	SetRootComponent(MeshComponent);
	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/GreenMaterial"));
}

// Called when the game starts or when spawned
void AHallwaySegment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHallwaySegment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHallwaySegment::GenerateSegment(float Width, float Depth)
{
	TArray<FVector> VerticesFloor = {FVector(0, 0, 0),
				FVector(0,  Width, 0),
				FVector(Depth, Width, 0),
				FVector(Depth, 0, 0)};
	TArray<FVector> VerticesWall1 = {FVector(0, 0, 0),
				FVector(0,  0, Width),
				FVector(Depth, 0, Width),
				FVector(Depth, 0, 0)};
	TArray<FVector> VerticesWall2 = {FVector(0, Width, 0),
				FVector(0,  Width, Width),
				FVector(Depth, Width, Width),
				FVector(Depth, Width, 0)};
	TArray<FVector2D> UVCoords = {FVector2D(0, 0), FVector2D(0, 1), FVector2D(1, 1), FVector2D(1, 0)};
	TArray<int32> Triangles = {1, 2, 3, 1, 3, 0};

	TArray<FVector> NormalsFloors;
	TArray<FProcMeshTangent> TangentsFloor;

	TArray<FVector> NormalsWall1;
	TArray<FProcMeshTangent> TangentsWall1;

	TArray<FVector> NormalsWall2;
	TArray<FProcMeshTangent> TangentsWall2;

	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(VerticesFloor, Triangles, UVCoords, NormalsFloors, TangentsFloor);
	//UKismetProceduralMeshLibrary::CalculateTangentsForMesh(VerticesWall1, Triangles, UVCoords, NormalsWall1, TangentsWall1);
	//UKismetProceduralMeshLibrary::CalculateTangentsForMesh(VerticesWall2, Triangles, UVCoords, NormalsWall2, TangentsWall2);
	
	MeshComponent->CreateMeshSection(0, VerticesFloor, Triangles, NormalsFloors, UVCoords, TArray<FColor>(), TangentsFloor, true);
	//MeshComponent->CreateMeshSection(1, VerticesWall1, Triangles, NormalsWall1, UVCoords, TArray<FColor>(), TangentsWall1, true);
	//MeshComponent->CreateMeshSection(2, VerticesWall2, Triangles, NormalsWall2, UVCoords, TArray<FColor>(), TangentsWall2, true);

	MeshComponent->SetMaterial(0, Material);
	//MeshComponent->SetMaterial(1, Material);
	//MeshComponent->SetMaterial(2, Material);
}

