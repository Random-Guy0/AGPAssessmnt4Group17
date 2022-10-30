// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "GridMeshSegment.generated.h"

UCLASS()
class AGPASSESSMNT4GROUP17_API AGridMeshSegment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridMeshSegment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* MeshComponent;

	FVector2D Position;

	void SetPosition(FVector2D PositionArg);
	void GenerateMesh(float GridSize, float RoomHeight, bool bGenLeftWall, bool bGenRightWall, bool bGenTopWall, bool bGenBottomWall);

private:
	UMaterialInterface* Material;
};
