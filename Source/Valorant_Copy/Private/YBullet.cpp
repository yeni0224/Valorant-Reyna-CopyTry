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

	//1. �浹ü ����ϱ�(�Ѿ��� �߻��ϴ� ��ü : ��)
	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	//2. �浹 �������� ����
	collisionComp->SetCollisionProfileName(TEXT("BlockAll"));
	//3. �浹ü ũ�� ����
	collisionComp->SetSphereRadius(13);
	//4. ��Ʈ�� ���
	RootComponent = collisionComp;

	/*�ܰ� StaticMesh ����*/	
	//5. �ܰ� ������Ʈ ����ϱ�
	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMeshComp"));
	//6. �θ� ������Ʈ ����
	bodyMeshComp->SetupAttachment(collisionComp);
	//7. �浹 ��Ȱ��ȭ
	bodyMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//8. �ܰ� ũ�� ����
	bodyMeshComp->SetRelativeScale3D(FVector(0.2f));

	//�����ֱ�
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

	//�Ѿ� �̵��� ��ġ������ ����ؼ� ����
	direction = GetActorForwardVector();
	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);

}

void AYBullet::DestroyMySelf()
{
	GetWorld()->GetTimerManager().SetTimer(lifeTimer, this, &AYBullet::DestroyMySelf, 1.5f, false);
}

void AYBullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
	//���� �Ѿ��� �浹������

}


