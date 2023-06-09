// Fill out your copyright notice in the Description page of Project Settings.


#include "HubActor.h"
#include "Engine/World.h"
// Sets default values
AHubActor::AHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHubActor::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (World)
	{
		for (int32 i = 0; i < 10; i++) 
		{
			  
				const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0, 300*i, 300));
				AMyActor* Geometry = World->SpawnActor<AMyActor>(GeometryClass, GeometryTransform);
			if (Geometry) 
			{ 
				FGeometryData Data;
				Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				Geometry->SetGeometryData(Data);
			}
		}
		for (int32 i = 0; i < 10; i++) 
		{
			  
				const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0, 300*i, 700));
				AMyActor* Geometry = World->SpawnActorDeferred<AMyActor>(GeometryClass, GeometryTransform);
			if (Geometry) 
			{ 
				FGeometryData Data;
				Data.Color = FLinearColor::MakeRandomColor();
				Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				Geometry->SetGeometryData(Data);
				Geometry->FinishSpawning(GeometryTransform);
			}
		}
		for (const FGeometryPayload Payload : GeometryPayloads)
		{
			AMyActor* Geometry = World->SpawnActorDeferred<AMyActor>(Payload.GeometryClass, Payload.InitialTransform);
			if (Geometry)
			{
				Geometry->SetGeometryData(Payload.Data);
				Geometry->FinishSpawning(Payload.InitialTransform);
			}
			 
		}
	} 
}

// Called every frame
void AHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

