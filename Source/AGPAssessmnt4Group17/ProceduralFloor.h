// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralFloor.generated.h"

UCLASS()
class AGPASSESSMNT4GROUP17_API AProceduralFloor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProceduralFloor();


	void SetSizeFloor(float Width, float Depth);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	float FloorWidth;
	float FloorDepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor, meta = (AllowPrivateAccess = "true")) // allows chacnges to be done in blueprint so longit is of the same class
		USceneComponent* Floor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> BushClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> RockClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> CoffinClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> StatueClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> PillarClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> BarrelClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> BoardClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> BoxClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> CartClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> HayClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> LogClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floor, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> TripleBarrelClass;

	void SpawnBush(UClass* BushToSpawn); //since BushClass references a BP it works with UClass
	void SpawnRock(UClass* RockToSpawn);
	void SpawnCoffin(UClass* CoffinToSpawn);
	void SpawnStatue(UClass* StatueToSpawn);
	void SpawnPillar(UClass* PillarToSpawn);
	void SpawnBarrel(UClass* BarrelToSpawn);
	void SpawnBoard(UClass* BoardToSpawn);
	void SpawnBox(UClass* BoxToSpawn);
	void SpawnCart(UClass* CartToSpawn);
	void SpawnHay(UClass* HayToSpawn);
	void SpawnLog(UClass* LogToSpawn);
	void SpawnTripleBarrel(UClass* TripleBarrelToSpawn);

};
