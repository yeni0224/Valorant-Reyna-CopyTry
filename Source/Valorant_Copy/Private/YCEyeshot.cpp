// Fill out your copyright notice in the Description page of Project Settings.
// ������Ʈ �����, ������ �����ϰ�, �浹 ������ �����, ���� �Ÿ����� ī�޶� �ü����� �߻��ϵ���


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
	
	//������ �̺�Ʈ�� �߻��ϵ��� �����Ѵ�
	sphereComp2->SetGenerateOverlapEvents(true);

	//�Ѿ� �ݸ����� �浹 ó�� �������� "YCEyeshotPreset"���� �����Ѵ�
	sphereComp2->SetCollisionProfileName(TEXT("YCEyeshotPreset"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeScale3D(FVector(0.3f));

	//������� ��ġ
	meshComp->SetRelativeLocation(FVector(0, 0, -50.0f));
}

// Called when the game starts or when spawned
void AYCEyeshot::BeginPlay()
{
	Super::BeginPlay();

	//�浹(overlap)�� �߻��ϸ� ������ �Լ��� �����Ѵ�	
	sphereComp2->OnComponentBeginOverlap.AddDynamic(this, &AYCEyeshot::OnOverlap);


	//�¾ �� 5�� �ڿ� �����Ѵ�.
	                                                                 //������ �Լ�  �� ����, �ݺ� �� ����
	GetWorld()->GetTimerManager().SetTimer(lifeTimer, this, &AYCEyeshot::DestroySelf, 4.0f, false);


	
}

// Called every frame
void AYCEyeshot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//direction = FVector(1, 0, 0); world direction
	// ���� ���� �������� ��� �̵��ϰ� �ʹ�
	direction = GetActorForwardVector();

	
	if (eyeshotDistance > 500) {
		eyeshotSpeed = 0; // 500��ŭ �̵��ϸ� ����
		
	}

	//��ġ �̵�
	SetActorLocation(GetActorLocation() + direction * eyeshotSpeed * DeltaTime);
	eyeshotDistance = eyeshotDistance + (eyeshotSpeed * DeltaTime);


	//���ѽ�ų�� ������ ��������

	if (bIsSpawnSightBlock)
	{
		//�ݱ� ����
		SpawnSightBlock();

			//����� �þ߰� �������� 
			//Collision�� ����µ� �ű⿡ player�� ������ �þ߰� ���ܵǵ��� ������ �����
			//(�ƿ� ȭ���� �������� ����������) (����ó��)
	}

}



void AYCEyeshot::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AYCEyeshot::DestroySelf() {
	Destroy();
}

void AYCEyeshot::SpawnSightBlock() {
	
	//�þ����� �ݱ��� �����Ѵ�
	GetWorld()->SpawnActor<AYCEyeshot>(sightBlock, FVector(0, 0, 0), FRotator::ZeroRotator);
	UE_LOG(LogTemp, Warning, TEXT("Spawn SightBlock"));

	

}

