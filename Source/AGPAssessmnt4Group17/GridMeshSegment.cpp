// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMeshSegment.h"

#include "KismetProceduralMeshLibrary.h"

// Sets default values
AGridMeshSegment::AGridMeshSegment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("Mesh Component");
	SetRootComponent(MeshComponent);
	MeshComponent->bCastShadowAsTwoSided = true;

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/StoneBrickMaterial"));
}

// Called when the game starts or when spawned
void AGridMeshSegment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridMeshSegment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridMeshSegment::SetPosition(FVector2D PositionArg)
{
	Position = PositionArg;
}

void AGridMeshSegment::GenerateMesh(float GridSize, float RoomHeight, bool bGenLeftWall, bool bGenRightWall, bool bGenTopWall, bool bGenBottomWall)
{
	TArray<FVector> VerticesFloor = {
		FVector(0, 0, 0),
		FVector(0, GridSize, 0),
		FVector(GridSize, GridSize, 0),
		FVector(GridSize, 0, 0 )
	};

	TArray<int32> TrianglesFloor = {
		0, 1, 2,
		0, 2, 3
	};

	TArray<FVector2D> UVCoords = {
		FVector2D(0, 0),
		FVector2D(0, 1),
		FVector2D(1, 1),
		FVector2D(1, 0)
	};

	TArray<FVector> NormalsFloor;
	TArray<FProcMeshTangent> TangentsFloor;

	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(VerticesFloor, TrianglesFloor, UVCoords, NormalsFloor, TangentsFloor);

	MeshComponent->CreateMeshSection(0, VerticesFloor, TrianglesFloor, NormalsFloor, UVCoords, TArray<FColor>(), TangentsFloor, true);

	MeshComponent->SetMaterial(0, Material);

	TArray<FVector> VerticesRoof = {
		FVector(0, 0, RoomHeight),
		FVector(0, GridSize, RoomHeight),
		FVector(GridSize, GridSize, RoomHeight),
		FVector(GridSize, 0, RoomHeight)
	};

	TArray<int32> TrianglesRoof = {
		0, 1, 2,
		0, 2, 3
	};

	TArray<FVector> NormalsRoof;
	TArray<FProcMeshTangent> TangentsRoof;

	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(VerticesRoof, TrianglesRoof, UVCoords, NormalsRoof, TangentsRoof);

	MeshComponent->CreateMeshSection(1, VerticesRoof, TrianglesRoof, NormalsRoof, UVCoords, TArray<FColor>(), TangentsRoof, true);

	MeshComponent->SetMaterial(1, Material);

	if(bGenLeftWall)
	{
		TArray<FVector> VerticesLeft = {
			FVector(0, 0, 0),
			FVector(0, 0, RoomHeight),
			FVector(GridSize, 0, RoomHeight),
			FVector(GridSize, 0, 0 )
		};

		TArray<int32> TrianglesLeft = {
			0, 1, 2,
			0, 2, 3
		};

		TArray<FVector> NormalsLeft;
		TArray<FProcMeshTangent> TangentsLeft;

		UKismetProceduralMeshLibrary::CalculateTangentsForMesh(VerticesLeft, TrianglesLeft, UVCoords, NormalsLeft, TangentsLeft);

		MeshComponent->CreateMeshSection(2, VerticesLeft, TrianglesLeft, NormalsLeft, UVCoords, TArray<FColor>(), TangentsLeft, true);

		MeshComponent->SetMaterial(2, Material);
	}

	if(bGenRightWall)
	{
		TArray<FVector> VerticesRight = {
			FVector(0, GridSize, 0),
			FVector(0, GridSize, RoomHeight),
			FVector(GridSize, GridSize, RoomHeight),
			FVector(GridSize, GridSize, 0 )
		};

		TArray<int32> TrianglesRight = {
			0, 1, 2,
			0, 2, 3
		};

		TArray<FVector> NormalsRight;
		TArray<FProcMeshTangent> TangentsRight;

		UKismetProceduralMeshLibrary::CalculateTangentsForMesh(VerticesRight, TrianglesRight, UVCoords, NormalsRight, TangentsRight);

		MeshComponent->CreateMeshSection(3, VerticesRight, TrianglesRight, NormalsRight, UVCoords, TArray<FColor>(), TangentsRight, true);

		MeshComponent->SetMaterial(3, Material);
	}

	if(bGenTopWall)
	{
		TArray<FVector> VerticesTop = {
			FVector(GridSize, 0, 0),
			FVector(GridSize, 0, RoomHeight),
			FVector(GridSize, GridSize, RoomHeight),
			FVector(GridSize, GridSize, 0 )
		};

		TArray<int32> TrianglesTop = {
			0, 1, 2,
			0, 2, 3
		};

		TArray<FVector> NormalsTop;
		TArray<FProcMeshTangent> TangentsTop;

		UKismetProceduralMeshLibrary::CalculateTangentsForMesh(VerticesTop, TrianglesTop, UVCoords, NormalsTop, TangentsTop);

		MeshComponent->CreateMeshSection(4, VerticesTop, TrianglesTop, NormalsTop, UVCoords, TArray<FColor>(), TangentsTop, true);

		MeshComponent->SetMaterial(4, Material);
	}

	if(bGenBottomWall)
	{
		TArray<FVector> VerticesBottom = {
			FVector(0, 0, 0),
			FVector(0, 0, RoomHeight),
			FVector(0, GridSize, RoomHeight),
			FVector(0, GridSize, 0 )
		};

		TArray<int32> TrianglesBottom = {
			0, 1, 2,
			0, 2, 3
		};

		TArray<FVector> NormalsBottom;
		TArray<FProcMeshTangent> TangentsBottom;

		UKismetProceduralMeshLibrary::CalculateTangentsForMesh(VerticesBottom, TrianglesBottom, UVCoords, NormalsBottom, TangentsBottom);

		MeshComponent->CreateMeshSection(5, VerticesBottom, TrianglesBottom, NormalsBottom, UVCoords, TArray<FColor>(), TangentsBottom, true);

		MeshComponent->SetMaterial(5, Material);
	}
}


