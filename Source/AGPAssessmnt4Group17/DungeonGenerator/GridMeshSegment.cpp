// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMeshSegment.h"

#include "KismetProceduralMeshLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AGridMeshSegment::AGridMeshSegment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	MeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("Mesh Component");;
	MeshComponent->bCastShadowAsTwoSided = true;
	SetRootComponent(MeshComponent);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/StoneBrickMaterial"));

	TorchSpawnChance = 0.45;
	TorchBlueprint = ConstructorHelpers::FClassFinder<AActor>(TEXT("/Game/Blueprints/TorchBlueprint")).Class;
}

// Called when the game starts or when spawned
void AGridMeshSegment::BeginPlay()
{
	Super::BeginPlay();

	GenerateMesh();
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

void AGridMeshSegment::SetMeshDetails(float GridSizeArg, float RoomHeightArg, bool bGenLeftWallArg,
	bool bGenRightWallArg, bool bGenTopWallArg, bool bGenBottomWallArg)
{
	GridSize = GridSizeArg;
	RoomHeight = RoomHeightArg;
	bGenLeftWall = bGenLeftWallArg;
	bGenRightWall = bGenRightWallArg;
	bGenTopWall = bGenTopWallArg;
	bGenBottomWall = bGenBottomWallArg;
}

void AGridMeshSegment::GenerateMesh()
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

		float TorchChance = FMath::RandRange(0.0f, 1.0f);

		if(TorchChance <= TorchSpawnChance && HasAuthority())
			GetWorld()->SpawnActor<AActor>(TorchBlueprint, GetActorLocation() + FVector(GridSize / 2.0f, 20, RoomHeight / 2.0f), FRotator::ZeroRotator);
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

		float TorchChance = FMath::RandRange(0.0f, 1.0f);

		if(TorchChance <= TorchSpawnChance && HasAuthority())
			GetWorld()->SpawnActor<AActor>(TorchBlueprint, GetActorLocation() + FVector(GridSize / 2.0f, GridSize - 20, RoomHeight / 2.0f), FRotator(0, 180, 0));
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

		float TorchChance = FMath::RandRange(0.0f, 1.0f);

		if(TorchChance <= TorchSpawnChance && HasAuthority())
			GetWorld()->SpawnActor<AActor>(TorchBlueprint, GetActorLocation() + FVector(GridSize - 20, GridSize / 2.0f, RoomHeight / 2.0f), FRotator(0, 90, 0));
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

		float TorchChance = FMath::RandRange(0.0f, 1.0f);

		if(TorchChance <= TorchSpawnChance && HasAuthority())
			GetWorld()->SpawnActor<AActor>(TorchBlueprint, GetActorLocation() + FVector(20, GridSize / 2.0f, RoomHeight / 2.0f), FRotator(0, -90, 0));
	}
}

void AGridMeshSegment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGridMeshSegment, GridSize);
	DOREPLIFETIME(AGridMeshSegment, RoomHeight);
	DOREPLIFETIME(AGridMeshSegment, bGenLeftWall);
	DOREPLIFETIME(AGridMeshSegment, bGenRightWall);
	DOREPLIFETIME(AGridMeshSegment, bGenTopWall);
	DOREPLIFETIME(AGridMeshSegment, bGenBottomWall);
}


