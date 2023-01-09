// Fill out your copyright notice in the Description page of Project Settings.
// 오브젝트 만들고, 스케일 조정하고, 충돌 프리셋 만들고, 일정 거리까지 카메라 시선으로 발사하도록


#include "YCEyeshot.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "YSightBlock.h"

// Sets default values
AYCEyeshot::AYCEyeshot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	

	sphereComp2 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(sphereComp2);
	sphereComp2->SetSphereRadius(50.0f);
	
	//오버랩 이벤트가 발생하도록 설정한다
	sphereComp2->SetGenerateOverlapEvents(true);

	//총알 콜리전의 충돌 처리 프리셋을 "YCEyeshotPreset"으로 설정한다
	sphereComp2->SetCollisionProfileName(TEXT("YCEyeshotPreset"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeScale3D(FVector(0.3f));

	//상대적인 위치
	meshComp->SetRelativeLocation(FVector(0, 0, -50.0f));
}

// Called when the game starts or when spawned
void AYCEyeshot::BeginPlay()
{
	Super::BeginPlay();

	//충돌(overlap)이 발생하면 실행할 함수를 연결한다	
	sphereComp2->OnComponentBeginOverlap.AddDynamic(this, &AYCEyeshot::OnOverlap);


	//태어난 후 5초 뒤에 제거한다.
	                                                                 //실행할 함수  초 설정, 반복 참 거짓
	GetWorld()->GetTimerManager().SetTimer(lifeTimer, this, &AYCEyeshot::DestroySelf, 4.0f, false);


	
}

// Called every frame
void AYCEyeshot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//direction = FVector(1, 0, 0); world direction
	// 나의 정면 방향으로 계속 이동하고 싶다
	direction = GetActorForwardVector();

	
	if (eyeshotDistance > 500) {
		eyeshotSpeed = 0; // 500만큼 이동하면 멈춤
		
	}

	//위치 이동
	SetActorLocation(GetActorLocation() + direction * eyeshotSpeed * DeltaTime);
	eyeshotDistance = eyeshotDistance + (eyeshotSpeed * DeltaTime);


	//눈총스킬이 앞으로 던져지면

	if (bIsSpawnSightBlock)
	{
		//반구 생성
		SpawnSightBlock();

			//상대의 시야가 가려진다 
			//Collision을 만드는데 거기에 player가 닿으면 시야가 차단되도록 위젯을 만든다
			//(아예 화면을 사진으로 가려버리기) (섬광처럼)
	}

}



void AYCEyeshot::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AYCEyeshot::DestroySelf() {
	Destroy();
}

void AYCEyeshot::SpawnSightBlock() {
	
	//시야차단 반구를 생성한다
	GetWorld()->SpawnActor<AYCEyeshot>(sightBlock, FVector(0, 0, 0), FRotator::ZeroRotator);
	UE_LOG(LogTemp, Warning, TEXT("Spawn SightBlock"));

	

}

