// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString(TEXT("Score:")), false);
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::FromInt(hitScore), false); //printer score


	SphereRadius = 25.f;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MySphereComponent"));

	CollisionSphere->InitSphereRadius(SphereRadius);
	CollisionSphere->SetCollisionProfileName("Trigger");

	RootComponent = CollisionSphere;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MyMesh->SetupAttachment(RootComponent);

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	movement(DeltaTime);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 20, FColor::Purple, false, -1, 0, 1);


	Super::Tick(DeltaTime);

	TimeLived += DeltaTime;
	if(TimeLived > timeBeforeDestroy)
	{
		Destroy();
	}


}



void AProjectile::movement(float DeltaTime)
{

	FVector NewLocation = GetActorLocation();

	NewLocation += GetActorForwardVector() * speed * DeltaTime;  //deltatime er vær frame og forhindrer at mer frames = raskere
	SetActorLocation(NewLocation);

}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if((OtherActor != nullptr) && (OtherActor != this ) && (OtherComp != nullptr) )
	{
		this->Destroy();
		//hitScore++;  //fungerte ikke pga starter på nytt får vær kule, må være en løsning på dette?

		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::FromInt(hitScore), false);
	}
} 