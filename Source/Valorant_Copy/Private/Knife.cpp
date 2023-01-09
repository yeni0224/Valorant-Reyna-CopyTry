// Fill out your copyright notice in the Description page of Project Settings.


#include "Knife.h"

// Sets default values
AKnife::AKnife()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKnife::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKnife::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);

}

void AKnife::KnifeThrowing()
{

	
	APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	//FVector camLocation = camManager->GetCameraLocation();
	FVector camForward = camManager->GetCameraRotation().Vector();

	direction = camForward;

}

void AKnife::KnifeDirectionReset()
{
	direction = FVector(0, 0, 0);
}