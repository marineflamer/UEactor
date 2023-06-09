// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "MyActor.generated.h"
UENUM(BlueprintType)
enum class EMovementType:uint8
{
	Sin, Static
};
USTRUCT(BlueprintType)
struct FGeometryData 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Movemennt")
	EMovementType MoveType = EMovementType::Static;

	UPROPERTY(EditAnywhere, Category = "Movemennt")
		float amplitude = 50.0f;
	
	UPROPERTY(EditAnywhere, Category = "Movemennt")
		float frequency = 2.0f;
	UPROPERTY(EditAnywhere, Category = "Design")
	FLinearColor Color = FLinearColor::Black;

	UPROPERTY(EditAnywhere, Category = "Design")
	float TimerRate = 3.0f;
};
UCLASS()
class MYPROJECT_API AMyActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyActor();
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BaseMesh;
	void SetGeometryData(const FGeometryData& Data) { GeometryData = Data; }
protected:
	// Called when the game starts or when spawned
	
	
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "GeometryData")
	FGeometryData GeometryData;

	UPROPERTY(EditAnywhere, Category = "Name")
		FString name = "amogus";
	UPROPERTY(EditDefaultsOnly, Category = "Stat")
		int32 kills = 7;
	UPROPERTY(EditAnywhere, Category = "Weapons")
		int32 weapons = 4;
	UPROPERTY(EditInstanceOnly, Category = "Health")
		float health = 68.415f;
	UPROPERTY(EditAnywhere, Category = "Health")
		bool isdead = false;
	UPROPERTY(VisibleAnywhere, Category = "Weapons")
		bool eqweapon = true;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	FTimerHandle TimerHandle;
	FVector InitialLocation; 
	const int32 MaxTimerCount = 20;
	int32 TimerCount = 0;
	void printStringTypes();
	void printTypes();
	void SetColor(const FLinearColor& Color);
	void OnTimerFired();
	void HandleMovement();
};
