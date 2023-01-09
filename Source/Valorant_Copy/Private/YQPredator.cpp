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

	//오버랩 이벤트가 발생하도록 설정한다
	sphereComp1->SetGenerateOverlapEvents(true); //나만 보이고, 상대방은 내가 보이지 않는 함수 작성까지 연결하기

	

	//총알 콜리전의 충돌 처리 프리셋을 "YCEyeshotPreset"으로 설정한다
	sphereComp1->SetCollisionProfileName(TEXT("YQPredatorPreset"));

	meshComp1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp1->SetupAttachment(RootComponent);
	meshComp1->SetRelativeScale3D(FVector(0.3f));

	//상대적인 위치
	meshComp1->SetRelativeLocation(FVector(0, 0, -50.0f));

}

// Called when the game starts or when spawned
void AYQPredator::BeginPlay()
{
	Super::BeginPlay();


	//충돌(overlap)이 발생하면 실행할 함수를 연결한다
	sphereComp1->OnComponentBeginOverlap.AddDynamic(this, &AYQPredator::OnOverlap);


	//태어난 후 5초 뒤에 제거한다.
																	 //실행할 함수  초 설정, 반복 참 거짓
	GetWorld()->GetTimerManager().SetTimer(lifeTimer, this, &AYQPredator::DestroySelf, 5.0f, false);
	
}

// Called every frame
void AYQPredator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//계속 나의 정면방향으로 이동
	direction = GetActorForwardVector();

	//500 이동하면 
	if (predatorDistance > 500) {
		
		//속도가 멈춘다
		predatorSpeed = 0;
		//UE_LOG(LogTemp, Warning, TEXT("predator stop"));

		//DeltaTime을 4초가 지나면 (4초가 지났는지 확인)
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

