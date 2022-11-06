// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralFloor.h"


// Sets default values
AProceduralFloor::AProceduralFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorComponent"));
	SetRootComponent(Floor);


}

// Called when the game starts or when spawned
void AProceduralFloor::BeginPlay()
{
	Super::BeginPlay();
	int32 NumberObjects = FMath::RandRange(30, 75);
	for (int32 i = 0; i < NumberObjects; i++)
	{
		SpawnBush(BushClass);
	}
	for (int32 i = 0; i < NumberObjects; i++)
	{
		SpawnRock(RockClass);
	}	
	for (int32 i = 0; i < NumberObjects; i++)
	{
		SpawnCoffin(CoffinClass);
	}
	for (int32 i = 0; i < NumberObjects; i++)
	{
		SpawnStatue(StatueClass);
	}
	for (int32 i = 0; i < NumberObjects; i++)
	{
		SpawnPillar(PillarClass);
	}
	for (int32 i = 0; i < NumberObjects; i++)
	{
		SpawnBarrel(BarrelClass);
	}
	for (int32 i = 0; i < NumberObjects; i++)
	{
		SpawnBoard(BoardClass);
	}
	for (int32 i = 0; i < NumberObjects; i++)
	{
		SpawnBox(BoxClass);
	}
	for (int32 i = 0; i < NumberObjects; i++)
	{
		SpawnCart(CartClass);
	}
	for (int32 i = 0; i < NumberObjects; i++)
	{
		SpawnHay(HayClass);
	}
	for (int32 i = 0; i < NumberObjects; i++)
	{
		SpawnLog(LogClass);
	}
	for (int32 i = 0; i < NumberObjects; i++)
	{
		SpawnTripleBarrel(TripleBarrelClass);
	}
}

// Called every frame
void AProceduralFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProceduralFloor::SetSizeFloor(float Width, float Depth)
{
	FloorWidth = Width;
	FloorDepth = Depth;
}

void AProceduralFloor::SpawnBush(UClass* BushToSpawn)
{

	float XCoordinate = FMath::FRandRange(100.f, FloorWidth-100.f); 
	float YCoordinate = FMath::FRandRange(100.f, FloorDepth-100.f); 

	float Yaw = FMath::FRandRange(0.f, 360.f); // gives random value for the rotation

	FVector Location(XCoordinate, YCoordinate, 0.f); //getting a random location
	FRotator Rotation(0.f, Yaw, 0.f); //getting a random rotation

	GetWorld()->SpawnActor<AActor>(BushToSpawn, Location, Rotation);
}

void AProceduralFloor::SpawnRock(UClass* RockToSpawn)
{

	float XCoordinate = FMath::FRandRange(100.f, FloorWidth - 100.f);
	float YCoordinate = FMath::FRandRange(100.f, FloorDepth - 100.f);

	float Yaw = FMath::FRandRange(0.f, 360.f); // gives random value for the rotation

	FVector Location(XCoordinate, YCoordinate, 0.f); //getting a random location
	FRotator Rotation(0.f, Yaw, 0.f); //getting a random rotation

	GetWorld()->SpawnActor<AActor>(RockToSpawn, Location, Rotation);
}

void AProceduralFloor::SpawnCoffin(UClass* CoffinToSpawn)
{

	float XCoordinate = FMath::FRandRange(100.f, FloorWidth - 100.f);
	float YCoordinate = FMath::FRandRange(100.f, FloorDepth - 100.f);

	float Yaw = FMath::FRandRange(0.f, 360.f); // gives random value for the rotation

	FVector Location(XCoordinate, YCoordinate, 0.f); //getting a random location
	FRotator Rotation(0.f, Yaw, 0.f); //getting a random rotation

	GetWorld()->SpawnActor<AActor>(CoffinToSpawn, Location, Rotation);
}
void AProceduralFloor::SpawnStatue(UClass* StatueToSpawn)
{

	float XCoordinate = FMath::FRandRange(100.f, FloorWidth - 100.f);
	float YCoordinate = FMath::FRandRange(100.f, FloorDepth - 100.f);

	float Yaw = FMath::FRandRange(0.f, 360.f); // gives random value for the rotation

	FVector Location(XCoordinate, YCoordinate, 0.f); //getting a random location
	FRotator Rotation(0.f, Yaw, 0.f); //getting a random rotation

	GetWorld()->SpawnActor<AActor>(StatueToSpawn, Location, Rotation);
}
void AProceduralFloor::SpawnPillar(UClass* PillarToSpawn)
{

	float XCoordinate = FMath::FRandRange(100.f, FloorWidth - 100.f);
	float YCoordinate = FMath::FRandRange(100.f, FloorDepth - 100.f);

	float Yaw = FMath::FRandRange(0.f, 360.f); // gives random value for the rotation

	FVector Location(XCoordinate, YCoordinate, 0.f); //getting a random location
	FRotator Rotation(0.f, Yaw, 0.f); //getting a random rotation

	GetWorld()->SpawnActor<AActor>(PillarToSpawn, Location, Rotation);
}

void AProceduralFloor::SpawnBarrel(UClass* BarrelToSpawn)
{

	float XCoordinate = FMath::FRandRange(100.f, FloorWidth - 100.f);
	float YCoordinate = FMath::FRandRange(100.f, FloorDepth - 100.f);

	float Yaw = FMath::FRandRange(0.f, 360.f); // gives random value for the rotation

	FVector Location(XCoordinate, YCoordinate, 0.f); //getting a random location
	FRotator Rotation(0.f, Yaw, 0.f); //getting a random rotation

	GetWorld()->SpawnActor<AActor>(BarrelToSpawn, Location, Rotation);
}

void AProceduralFloor::SpawnBoard(UClass* BoardToSpawn)
{

	float XCoordinate = FMath::FRandRange(100.f, FloorWidth - 100.f);
	float YCoordinate = FMath::FRandRange(100.f, FloorDepth - 100.f);

	float Yaw = FMath::FRandRange(0.f, 360.f); // gives random value for the rotation

	FVector Location(XCoordinate, YCoordinate, 0.f); //getting a random location
	FRotator Rotation(0.f, Yaw, 0.f); //getting a random rotation

	GetWorld()->SpawnActor<AActor>(BoardToSpawn, Location, Rotation);
}

void AProceduralFloor::SpawnBox(UClass* BoxToSpawn)
{

	float XCoordinate = FMath::FRandRange(100.f, FloorWidth - 100.f);
	float YCoordinate = FMath::FRandRange(100.f, FloorDepth - 100.f);

	float Yaw = FMath::FRandRange(0.f, 360.f); // gives random value for the rotation

	FVector Location(XCoordinate, YCoordinate, 0.f); //getting a random location
	FRotator Rotation(0.f, Yaw, 0.f); //getting a random rotation

	GetWorld()->SpawnActor<AActor>(BoxToSpawn, Location, Rotation);
}

void AProceduralFloor::SpawnCart(UClass* CartToSpawn)
{

	float XCoordinate = FMath::FRandRange(100.f, FloorWidth - 100.f);
	float YCoordinate = FMath::FRandRange(100.f, FloorDepth - 100.f);

	float Yaw = FMath::FRandRange(0.f, 360.f); // gives random value for the rotation

	FVector Location(XCoordinate, YCoordinate, 0.f); //getting a random location
	FRotator Rotation(0.f, Yaw, 0.f); //getting a random rotation

	GetWorld()->SpawnActor<AActor>(CartToSpawn, Location, Rotation);
}

void AProceduralFloor::SpawnHay(UClass* HayToSpawn)
{

	float XCoordinate = FMath::FRandRange(100.f, FloorWidth - 100.f);
	float YCoordinate = FMath::FRandRange(100.f, FloorDepth - 100.f);

	float Yaw = FMath::FRandRange(0.f, 360.f); // gives random value for the rotation

	FVector Location(XCoordinate, YCoordinate, 0.f); //getting a random location
	FRotator Rotation(0.f, Yaw, 0.f); //getting a random rotation

	GetWorld()->SpawnActor<AActor>(HayToSpawn, Location, Rotation);
}

void AProceduralFloor::SpawnLog(UClass* LogToSpawn)
{

	float XCoordinate = FMath::FRandRange(100.f, FloorWidth - 100.f);
	float YCoordinate = FMath::FRandRange(100.f, FloorDepth - 100.f);

	float Yaw = FMath::FRandRange(0.f, 360.f); // gives random value for the rotation

	FVector Location(XCoordinate, YCoordinate, 0.f); //getting a random location
	FRotator Rotation(0.f, Yaw, 0.f); //getting a random rotation

	GetWorld()->SpawnActor<AActor>(LogToSpawn, Location, Rotation);
}

void AProceduralFloor::SpawnTripleBarrel(UClass* TripleBarrelToSpawn)
{

	float XCoordinate = FMath::FRandRange(100.f, FloorWidth - 100.f);
	float YCoordinate = FMath::FRandRange(100.f, FloorDepth - 100.f);

	float Yaw = FMath::FRandRange(0.f, 360.f); // gives random value for the rotation

	FVector Location(XCoordinate, YCoordinate, 0.f); //getting a random location
	FRotator Rotation(0.f, Yaw, 0.f); //getting a random rotation

	GetWorld()->SpawnActor<AActor>(TripleBarrelToSpawn, Location, Rotation);
}