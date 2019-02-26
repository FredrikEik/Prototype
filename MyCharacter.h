// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pickup.h"

#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MyCharacter.generated.h"
UCLASS()
class TESTSTOROPPG_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* CubeMesh;
	UPROPERTY(EditAnywhere)
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	class USceneComponent* HoldingComponent;



UPROPERTY(EditAnywhere)
class APickup* CurrentItem;

bool bCanMove;
bool bHoldingItem;
bool bInspecting;

float PitchMax;
float PitchMin;

FVector HoldingComp;
FVector LastRotation;

FVector Start;
FVector ForwardVector;
FVector End;

FHitResult Hit;

FComponentQueryParams DefaultComponentQueryParams;
FCollisionResponseParams DefaultResponseParams;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void OnAction();

	void OnInspect();

	void OnInspectReleased();

	void ToggleMovement();

	void ToggleItemPickup();

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		void MoveForward(float Value);
		void MoveRight(float Value);

		
	
};
