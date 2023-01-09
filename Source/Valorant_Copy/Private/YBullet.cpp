// Fill out your copyright notice in the Description page of Project Settings.


#include "YBullet.h"
#include <Components/SphereComponent.h>
#include <GameFrameWork/ProjectileMovementComponent.h>
#include "Kismet/GameplayStatics.h"

// Sets default values
AYBullet::AYBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//1. 충돌체 등록하기(총알을 발사하는 주체 : 총)
	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	//2. 충돌 프로파일 설정
	collisionComp->SetCollisionProfileName(TEXT("BlockAll"));
	//3. 충돌체 크기 설정
	collisionComp->SetSphereRadius(13);
	//4. 루트로 등록
	RootComponent = collisionComp;

	/*외관 StaticMesh 설정*/	
	//5. 외관 컴포넌트 등록하기
	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMeshComp"));
	//6. 부모 컴포넌트 지정
	bodyMeshComp->SetupAttachment(collisionComp);
	//7. 충돌 비활성화
	bodyMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//8. 외관 크기 설정
	bodyMeshComp->SetRelativeScale3D(FVector(0.2f));

	//생명주기
	InitialLifeSpan = 1.5f;
}

// Called when the game starts or when spawned
void AYBullet::BeginPlay()
{
	Super::BeginPlay();
		
}

// Called every frame
void AYBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//총알 이동의 위치정보를 계속해서 전달
	direction = GetActorForwardVector();
	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);

}

void AYBullet::DestroyMySelf()
{
	GetWorld()->GetTimerManager().SetTimer(lifeTimer, this, &AYBullet::DestroyMySelf, 1.5f, false);
}

void AYBullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
	//상대와 총알이 충돌했을때

}


