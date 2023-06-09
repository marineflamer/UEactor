// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"
DEFINE_LOG_CATEGORY_STATIC(Sus, All, All)
// Sets default values
AMyActor::AMyActor()
{ 
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();

	FTransform Transform = GetActorTransform();
	FVector location = Transform.GetLocation();
	FRotator rotation = Transform.Rotator();
	FVector scale = Transform.GetScale3D();
	UE_LOG(Sus, Warning, TEXT("Transform: %s"), *Transform.ToString());
	UE_LOG(Sus, Warning, TEXT("loacation: %s"), *location.ToString());
	UE_LOG(Sus, Warning, TEXT("rotation: %s"), *rotation.ToString());
	UE_LOG(Sus, Warning, TEXT("scale: %s"), *scale.ToString());
	UE_LOG(Sus, Error, TEXT("Human Transform: %s"), *Transform.ToHumanReadableString());
	printStringTypes();
	printTypes();
	SetColor(GeometryData.Color);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyActor::OnTimerFired, GeometryData.TimerRate, true);

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleMovement();
	
}
void AMyActor::printTypes()
{

	UE_LOG(Sus, Warning, TEXT("Name: %s"), *GetName());
	UE_LOG(Sus, Warning, TEXT("Health: %f"), health);
	UE_LOG(Sus, Warning, TEXT("Has Weapon: %d"), eqweapon);
	UE_LOG(Sus, Warning, TEXT("Is Dead: %d"), isdead);
	UE_LOG(Sus, Warning, TEXT("Amogus Kills: %i"), kills);

}
void AMyActor::SetColor(const FLinearColor& Color)
{
	if (!BaseMesh) return;
	UMaterialInstanceDynamic* DynMat = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMat)
	{
		DynMat->SetVectorParameterValue("Color", Color);
	}
}
void AMyActor::OnTimerFired()
{
	if (++TimerCount < MaxTimerCount)
	{
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();
		UE_LOG(Sus, Display, TEXT("color to set up: %s Timer count: %i"), *NewColor.ToString(), TimerCount);
		SetColor(NewColor);
	}
	else
	{
		UE_LOG(Sus, Error, TEXT("Timer Has been stoped!"));
		GetWorldTimerManager().ClearTimer(TimerHandle);
		
	}
}
void AMyActor::HandleMovement()
{
	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin:
	{
		FVector CurrentLocation = GetActorLocation();
		if (GetWorld())
		{
			float time = GetWorld()->GetRealTimeSeconds();
			CurrentLocation.Z = InitialLocation.Z + GeometryData.amplitude * FMath::Sin(GeometryData.frequency * time);
			SetActorLocation(CurrentLocation);
		}

	}break;
	case EMovementType::Static:
	{

	}break;
	default: break;
	}
}
void AMyActor::printStringTypes()
{
	

	FString weaponsStr = "Weapons num: " + FString::FromInt(weapons);
	FString healthStr = "player have " + FString::SanitizeFloat(health);
	FString isdeadStr = "player is " + FString(isdead ? "dead" : "alive");
	FString Stat = FString::Printf(TEXT("\n Players statistics:\n%s\n%s\n%s"), *weaponsStr, *healthStr, *isdeadStr);

	UE_LOG(Sus, Warning, TEXT("%s"), *Stat);
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Emerald, name);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Emerald, Stat, true, FVector2D(2, 2));
	}
}