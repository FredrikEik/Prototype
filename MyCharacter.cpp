// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobject<UFloatingPawnMovement>("PawnMomevent");

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("CubeMesh"); // så vi kan se objektet/character
	//Camera = CreateDefaultSubobject<UCameraComponent>("Camera"); // lager kamera som skal følge Character

	HoldingComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HoldingComponent"));
	HoldingComponent->RelativeLocation.X = 50.f;
	HoldingComponent->SetupAttachment(CubeMesh);

	CurrentItem = NULL;
	bCanMove = true;
	bInspecting = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//PitchMax = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMax;
	//PitchMin = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMin;	
}



// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Start = CameraComponent->GetComponentLocation();
	//ForwardVector = CameraComponent->GetForwardVector();
	End = ((ForwardVector * 200.f) + Start);

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	/*if(!bHoldingItem)
	{
		if(GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, DefaultComponentQueryParams, DefaultResponseParams))
			{
				if(Hit.GetActor()->GetClass()->IsChildOf(APickup::StaticClass()))
				{
					CurrentItem = Cast<APickup>(Hit.GetActor());
				}
			}
				else {
		CurrentItem = NULL;
	}


	}

	if(bInspecting)
	{
		if(bHoldingItem)
		{
			//CameraComponent->SetFieldOfView(FMath::Lerp(CameraComponent->FieldOfView, 90.f, 0.1f));
			HoldingComponent->SetRelativeLocation(FVector(0.0f, 50.f, 50.f));
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMax = 179.9f;
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMin = -179.9f;
			CurrentItem->RotateActor();
		}
		//else
		//{
		//CameraComponent->SetFieldOfView(FMath::Lerp(CameraComponent->FieldOfView, 45.f, 0.1f));
		//}
	}
	else
	{
		//CameraComponent->SetFieldOfView(FMath::Lerp(CameraComponent->FieldOfView, 90.f, 0.1f));

		if(bHoldingItem)
		{
			HoldingComponent->SetRelativeLocation(FVector(50.f, 0.f, 0.f));
		}
	}
	*/
	

}
// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AMyCharacter::OnAction);
	PlayerInputComponent->BindAction("Inspect", IE_Pressed, this, &AMyCharacter::OnInspect);
	PlayerInputComponent->BindAction("Inspect", IE_Released, this, &AMyCharacter::OnInspectReleased);
}

void AMyCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AMyCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AMyCharacter::OnAction()
{
		if(CurrentItem && !bInspecting)
		{
			ToggleItemPickup();
		}
}

void AMyCharacter::OnInspect()
{
	if(bHoldingItem)
	{
	//LastRotation = GetControlRotation();
		ToggleMovement();
	}
	else{
		bInspecting = true;
	}
}

void AMyCharacter::OnInspectReleased()
{
	if(bInspecting && bHoldingItem)
	{
		//GetController()->SetControlRotation(LastRotation);
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMax = PitchMax;
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMin = PitchMin;

		ToggleMovement();
	}
	else
	{
		bInspecting = false;
	}
}

void AMyCharacter::ToggleMovement()
{
bCanMove = !bCanMove;
bInspecting = !bInspecting;

//CameraComponent->bUsePawnControlRotation = !CameraComponent->bUsePawnControlRotation;
bUseControllerRotationYaw = !bUseControllerRotationYaw;


}

void AMyCharacter::ToggleItemPickup()
{
	if(CurrentItem)
	{
		bHoldingItem = !bHoldingItem;
		CurrentItem->Pickup();

		if(!bHoldingItem)
		{
			CurrentItem = NULL;
		}
	}
}