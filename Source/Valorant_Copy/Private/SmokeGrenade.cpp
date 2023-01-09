// Fill out your copyright notice in the Description page of Project Settings.


#include "SmokeGrenade.h"



// Sets default values
ASmokeGrenade::ASmokeGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASmokeGrenade::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ASmokeGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	/*APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	//FVector camLocation = camManager->GetCameraLocation();
	FVector camForward = camManager->GetCameraRotation().Vector();

	direction = camForward;
	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);*/
	initS = 1;
	SetActorLocation(GetActorLocation() + FVector(initS * direction.X + initS * direction.Y + initS * direction.Z - 5* DeltaTime));
}

void ASmokeGrenade::KeepPressed()
{
	APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	angle = camManager->GetCameraRotation().Pitch;
	FVector camForward = camManager->GetCameraRotation().Vector();
	direction = camForward;
	keepPressed = true;
}

void ASmokeGrenade::ReleasedC()
{
	keepPressed = false;
	
}