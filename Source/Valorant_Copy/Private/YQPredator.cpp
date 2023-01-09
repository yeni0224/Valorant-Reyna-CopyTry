// Fill out your copyright notice in the Description page of Project Settings.


#include "YQPredator.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AYQPredator::AYQPredator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	sphereComp1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(sphereComp1);
	sphereComp1->SetSphereRadius(50.0f);

	//������ �̺�Ʈ�� �߻��ϵ��� �����Ѵ�
	sphereComp1->SetGenerateOverlapEvents(true); //���� ���̰�, ������ ���� ������ �ʴ� �Լ� �ۼ����� �����ϱ�

	

	//�Ѿ� �ݸ����� �浹 ó�� �������� "YCEyeshotPreset"���� �����Ѵ�
	sphereComp1->SetCollisionProfileName(TEXT("YQPredatorPreset"));

	meshComp1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp1->SetupAttachment(RootComponent);
	meshComp1->SetRelativeScale3D(FVector(0.3f));

	//������� ��ġ
	meshComp1->SetRelativeLocation(FVector(0, 0, -50.0f));

}

// Called when the game starts or when spawned
void AYQPredator::BeginPlay()
{
	Super::BeginPlay();


	//�浹(overlap)�� �߻��ϸ� ������ �Լ��� �����Ѵ�
	sphereComp1->OnComponentBeginOverlap.AddDynamic(this, &AYQPredator::OnOverlap);


	//�¾ �� 5�� �ڿ� �����Ѵ�.
																	 //������ �Լ�  �� ����, �ݺ� �� ����
	GetWorld()->GetTimerManager().SetTimer(lifeTimer, this, &AYQPredator::DestroySelf, 5.0f, false);
	
}

// Called every frame
void AYQPredator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//��� ���� ����������� �̵�
	direction = GetActorForwardVector();

	//500 �̵��ϸ� 
	if (predatorDistance > 500) {
		
		//�ӵ��� �����
		predatorSpeed = 0;
		//UE_LOG(LogTemp, Warning, TEXT("predator stop"));

		//DeltaTime�� 4�ʰ� ������ (4�ʰ� �������� Ȯ��)
		currentTime += DeltaTime;
		if (currentTime > 2) {
			predatorSpeed = 1000;
			//UE_LOG(LogTemp, Warning, TEXT("Speed is back"));

			direction *= -1;
			//UE_LOG(LogTemp, Warning, TEXT("Comingback predator"));

		}
		
	}

	SetActorLocation(GetActorLocation() + direction * DeltaTime * predatorSpeed);
	predatorDistance = predatorDistance + predatorSpeed * DeltaTime;

}

void AYQPredator::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AYQPredator::DestroySelf() 
{
	Destroy();
}

