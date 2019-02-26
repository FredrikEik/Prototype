// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TESTSTOROPPG_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

		void movement(float DeltaTime);

	UPROPERTY(EditAnywhere)
	float speed{-2500.f};

	UPROPERTY(EditAnywhere)
	float timeBeforeDestroy{5.f};
	
	UPROPERTY(EditAnywhere)
	class USphereComponent* CollisionSphere;
		UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MyMesh;

	float SphereRadius;

	float hitScore{0};

	float TimeLived = 0.f;
			
			UFUNCTION() 
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); 

};
