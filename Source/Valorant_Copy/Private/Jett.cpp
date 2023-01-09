// Fill out your copyright notice in the Description page of Project Settings.


#include "Jett.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SmokeGrenade.h"
#include "Knife.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

// Sets default values
AJett::AJett()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AJett::BeginPlay()
{
	Super::BeginPlay();

	const FVector LocationS = GetActorLocation();
	const FRotator RotationS = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(SmokeGrenade, LocationS, RotationS);
	for (TActorIterator<ASmokeGrenade>it(GetWorld()); it; ++it)
	{
		smoke = *it;
	}

	FVector Location = GetActorLocation() + FVector(0, 0, -200);
	DeactivatedLocation = Location;
	FRotator Rotation = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(Knife, Location, Rotation);
	for (TActorIterator<AKnife>it0(GetWorld()); it0; ++it0)
	{
		knife0 = *it0;
	}
;
	GetWorld()->SpawnActor<AActor>(Knife, Location, Rotation);
	for (TActorIterator<AKnife>it1(GetWorld()); it1; ++it1)
	{
		
		knife1 = *it1;
	}
	
	GetWorld()->SpawnActor<AActor>(Knife, Location, Rotation);
	for (TActorIterator<AKnife>it2(GetWorld()); it2; ++it2)
	{
		knife2 = *it2;
	}
	
	GetWorld()->SpawnActor<AActor>(Knife, Location, Rotation);
	for (TActorIterator<AKnife>it3(GetWorld()); it3; ++it3)
	{
		knife3 = *it3;
	}
	
	GetWorld()->SpawnActor<AActor>(Knife, Location, Rotation);
	for (TActorIterator<AKnife>it4(GetWorld()); it4; ++it4)
	{
		knife4 = *it4;
	}

	knifeArray.Add(knife0);
	knifeArray.Add(knife1);
	knifeArray.Add(knife2);
	knifeArray.Add(knife3);
	knifeArray.Add(knife4);

}

// Called every frame
void AJett::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DashDir = GetActorForwardVector();

	if (MaxKnife == 5)
	{

		//APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
		//FVector camLocation = camManager->GetCameraLocation();
		knife0->SetActorLocation(GetActorLocation() + GetActorForwardVector()* 200 + GetActorRightVector() * -200);
		knife1->SetActorLocation(GetActorLocation() + GetActorForwardVector()* 200 + GetActorRightVector() * 200);
		knife2->SetActorLocation(GetActorLocation() + GetActorForwardVector()* 200 + GetActorRightVector() * -100);
		knife3->SetActorLocation(GetActorLocation() + GetActorForwardVector()* 200 + GetActorRightVector() * 100);
		knife4->SetActorLocation(GetActorLocation() + GetActorForwardVector()* 200);

	}															  
	else if (MaxKnife == 4)
	{
		knife1->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * 200);
		knife2->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * -100);
		knife3->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * 100);
		knife4->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200);
	}
	else if (MaxKnife == 3)
	{
		knife2->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * -100);
		knife3->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * 100);
		knife4->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200);
	}
	else if (MaxKnife == 2)
	{
		knife3->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * 100);
		knife4->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200);
	}
	else if (MaxKnife == 1)
	{
		knife4->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200);
	}

}

// Called to bind functionality to input
void AJett::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AJett::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AJett::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &AJett::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &AJett::Vertical);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AJett::InputJump);
	PlayerInputComponent->BindAction(TEXT("Walking"), IE_Pressed, this, &AJett::Walking);
	PlayerInputComponent->BindAction(TEXT("Walking"), IE_Released, this, &AJett::WalkEnd);
	PlayerInputComponent->BindAction(TEXT("JumpDash"), IE_Pressed, this, &AJett::JumpDash);
	PlayerInputComponent->BindAction(TEXT("Dash"), IE_Pressed, this, &AJett::Dash);
	PlayerInputComponent->BindAction(TEXT("Smoke"), IE_Pressed, this, &AJett::Smoke);
	PlayerInputComponent->BindAction(TEXT("Smoke"), IE_Released, this, &AJett::SmokeControlEnd);
	PlayerInputComponent->BindAction(TEXT("KnifeSet"), IE_Pressed, this, &AJett::KnifeSetting);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AJett::Fire);
	PlayerInputComponent->BindAction(TEXT("FireSp"), IE_Pressed, this, &AJett::FireSp);
	
}

void AJett::Turn(float value)
{
	AddControllerYawInput(value);
}

void AJett::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void AJett::Horizontal(float value)
{
	direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	direction.Normalize();
	AddMovementInput(direction, value);
	//CharacterMoveDir = direction * value;
	//CharacterMoveDir.Z = 0;
	//CharacterMoveDir.Normalize();
	yValue = value;
}

void AJett::Vertical(float value)
{
	
	direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	direction.Normalize();
	AddMovementInput(direction, value);
	//CharacterMoveDir = direction * value;
	//CharacterMoveDir.Z = 0;
	//CharacterMoveDir.Normalize();
	xValue = value;
}

void AJett::InputJump()
{
	Jump();
}

void AJett::Walking()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void AJett::WalkEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = runSpeed;
}

void AJett::JumpDash()
{
	direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Z);
	direction.Normalize();
	LaunchCharacter(direction * jumpdashDistance, true, true);
	
}

void AJett::Dash()
{
	if (xValue == 0 && yValue == 0)
	{
		LaunchCharacter(GetActorForwardVector() * dashDistance, true, true);
	}
	else
	{
		DashDir.X = xValue;
		DashDir.Y = yValue;
		LaunchCharacter(GetActorRotation().RotateVector(DashDir) * dashDistance, true, true);
	}
}


void AJett::Smoke()
{

	smoke->KeepPressed();

}

void AJett::SmokeControlEnd()
{
	
	smoke->ReleasedC();
}


void AJett::KnifeSetting()
{
	if (MaxKnife == 0)
	{
		for (int32 i = 0; i < knifeArray.Num(); i++)
		{
			knifeArray[i]->KnifeDirectionReset();
		}
		MaxKnife = 5;
	}

}

void AJett::Fire()
{
	if (MaxKnife == 5)
	{
		knife0->KnifeThrowing();
		MaxKnife -= 1;

	}
	else if (MaxKnife == 4)
	{
		knife1->KnifeThrowing();
		MaxKnife -= 1;
	}
	else if (MaxKnife == 3)
	{
		knife2->KnifeThrowing();
		MaxKnife -= 1;
	}
	else if (MaxKnife == 2)
	{
		knife3->KnifeThrowing();
		MaxKnife -= 1;
	}
	else if (MaxKnife == 1)
	{
		knife4->KnifeThrowing();
		MaxKnife -= 1;
	}

}

void AJett::FireSp()
{

	if (MaxKnife == 5)
	{
		Fire();
		GetWorld()->GetTimerManager().SetTimer(KnifeTime, this, &AJett::Fire, 0.2f, false);
		GetWorld()->GetTimerManager().SetTimer(KnifeTime1, this, &AJett::Fire, 0.4f, false);
		GetWorld()->GetTimerManager().SetTimer(KnifeTime2, this, &AJett::Fire, 0.6f, false);
		GetWorld()->GetTimerManager().SetTimer(KnifeTime3, this, &AJett::Fire, 0.8f, false);
	
	}
	else if (MaxKnife == 4)
	{
		Fire();
		GetWorld()->GetTimerManager().SetTimer(KnifeTime, this, &AJett::Fire, 0.2f, false);
		GetWorld()->GetTimerManager().SetTimer(KnifeTime1, this, &AJett::Fire, 0.4f, false);
		GetWorld()->GetTimerManager().SetTimer(KnifeTime2, this, &AJett::Fire, 0.6f, false);
	}
	else if (MaxKnife == 3)
	{
		Fire();
		GetWorld()->GetTimerManager().SetTimer(KnifeTime, this, &AJett::Fire, 0.2f, false);
		GetWorld()->GetTimerManager().SetTimer(KnifeTime1, this, &AJett::Fire, 0.4f, false);
	}

	else if (MaxKnife == 2)
	{
		Fire();
		GetWorld()->GetTimerManager().SetTimer(KnifeTime, this, &AJett::Fire, 0.2f, false);
	}
	else if (MaxKnife == 1)
	{
		Fire();
	}

}
