// Fill out your copyright notice in the Description page of Project Settings.


#include "YSightBlock.h"
#include "Components/SphereComponent.h"
#include "YReyna.h"

// Sets default values
AYSightBlock::AYSightBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp3 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(sphereComp3);
	sphereComp3->SetSphereRadius(150.0f);


	//�Ѿ� �ݸ����� �浹 ó�� �������� "YCEyeshotPreset"���� �����Ѵ�
	sphereComp3->SetCollisionProfileName(TEXT("YQPredatorPreset"));

	meshComp3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp3->SetupAttachment(RootComponent);
	meshComp3->SetRelativeScale3D(FVector(0.3f));

	//meshComp3->SetOnlyOwnerSee(true); // ���� ���� ���� ������, ���� �ȿ� ���� �Լ��� ȣ��Ǿ �갡 Ȱ��ȭ �ǵ���

}

// Called when the game starts or when spawned
void AYSightBlock::BeginPlay()
{
	Super::BeginPlay();

		
	
}

// Called every frame
void AYSightBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AYSightBlock::DestroySelf()
{
	Destroy();
}

