// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootBullets.h"
#include "Gameframework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/ActorChannel.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraActor.h"
#include "Components/InputComponent.h"


// Sets default values for this component's properties
UShootBullets::UShootBullets()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShootBullets::BeginPlay()
{
	Super::BeginPlay();

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent found!"));

		InputComponent->BindAction("Shoot", IE_Pressed, this, &UShootBullets::Shoot);
		InputComponent->BindAction("Go_Left", IE_Pressed, this, &UShootBullets::Go_Left);
		InputComponent->BindAction("Go_Right", IE_Pressed, this, &UShootBullets::Go_Right);
		InputComponent->BindAction("Go_Left", IE_Released, this, &UShootBullets::StopMoving);
		InputComponent->BindAction("Go_Right", IE_Released, this, &UShootBullets::StopMoving);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component not found!"))
	}
}

void UShootBullets::Shoot()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed the Shoot Key!"));


}

void UShootBullets::Go_Left()
{
	UE_LOG(LogTemp, Warning, TEXT("Going Left!"));

	CurrentVelocity = { 0.0f, -100.0f, 0.0f };
}
void UShootBullets::Go_Right()
{
	UE_LOG(LogTemp, Warning, TEXT("Going Right!"));

	CurrentVelocity = { 0.0f, 100.0f, 0.0f };
}

void UShootBullets::StopMoving()
{
	CurrentVelocity = { 0.0f, 0.0f, 0.0f };
}


// Called every frame
void UShootBullets::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	Movement(DeltaTime);
	// ...
}

void UShootBullets::Movement(float DeltaTime)
{
	if ((GetOwner()->GetActorLocation().Y < LeftBoundaries && CurrentVelocity.Y < 0.0f) || (GetOwner()->GetActorLocation().Y > RightBoundaries && CurrentVelocity.Y > 0.0f))
	{
		CurrentVelocity = { 0.0f, 0.0f, 0.0f };
	}
	TimeAccellerating += DeltaTime;
	if (!CurrentVelocity.IsZero())
	{
		if (TimeAccellerating > TimeBeforeAccelerate)
		{
			SpeedScale += 0.05;
			SpeedScale > 5.0f ? SpeedScale = 4.0f : SpeedScale;


		}

		FVector NewLocation = GetOwner()->GetActorLocation() + (CurrentVelocity * SpeedScale * DeltaTime);
		GetOwner()->SetActorLocation(NewLocation);
	}
	else
	{
		SpeedScale = 2.5f;
		TimeAccellerating = 0.f;
	}
}