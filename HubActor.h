// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.h"
#include "HubActor.generated.h"

USTRUCT(BlueprintType)
struct FGeometryPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		TSubclassOf<AMyActor>GeometryClass;
	UPROPERTY(EditAnywhere)
		FGeometryData Data;
	UPROPERTY(EditAnywhere)
		FTransform InitialTransform;
		
};
UCLASS()
class MYPROJECT_API AHubActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHubActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AMyActor>GeometryClass; 
	
	UPROPERTY(EditAnywhere)
		UClass* Class;
	
	UPROPERTY(EditAnywhere)
		AMyActor* GeometryObject;

	UPROPERTY(EditAnywhere)
		TArray<FGeometryPayload>GeometryPayloads;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
