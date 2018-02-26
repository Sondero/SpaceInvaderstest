// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "ShootBullets.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEINVADERS_API UShootBullets : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootBullets();

	float BoundaryL = -400.0f;
	float BoundaryR = 400.0f;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere)
	float LeftBoundaries = -350.0f;
	UPROPERTY(EditAnywhere)
	float RightBoundaries = 350.0f;

	UPROPERTY(EditAnywhere)
	float SpeedScale = 1.f;
	float TimeBeforeAccelerate = 1.f;
	float TimeAccellerating{ 0.f };

private:
	UInputComponent* InputComponent = nullptr;
	
	void Shoot();
	void Go_Left();
	void Go_Right();
	void StopMoving();

	float Speed = 2.0f;
	
	void Movement(float DeltaTime);
};
