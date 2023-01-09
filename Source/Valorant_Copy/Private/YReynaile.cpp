// Fill out your copyright notice in the Description page of Project Settings.


#include "YReynaile.h"


// Sets default values
AYReynaile::AYReynaile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent) 
	{	
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	if (!CollisionComp) {
		//�浹ü�� ǥ���ϱ� ���� ������ ����Ѵ�
		CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

		//���� �浹ü �̸� ����
		CollisionComp->BodyInstance.SetCollisionProfileName(TEXT("YReynaile"));

		//�浹ü�� �浹�� �� �̺�Ʈ ȣ���ϱ�
		CollisionComp->OnComponentHit.AddDynamic(this, &AYReynaile::OnHit);

		//Sphere(����) ũ�� ����
		CollisionComp->InitSphereRadius(15.0f);

		//�浹ü�� ��Ʈ������Ʈ�� ����
		RootComponent = CollisionComp;
	}

	if (!yReynaileMoveComp) 
	{
		//�� ������Ʈ ������ ��Ʈ�� �����ϱ�
		yReynaileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("yReynaMovComp"));
		yReynaileMoveComp->SetUpdatedComponent(CollisionComp);
		yReynaileMoveComp->bRotationFollowsVelocity = true;
		yReynaileMoveComp->bShouldBounce = true;
		yReynaileMoveComp->Bounciness = 0.3f;
		yReynaileMoveComp->ProjectileGravityScale = 0.0f;

	}

	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
		if (Mesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		}

		static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/Y_BP/SphereMaterial.SphereMaterial'"));
		if (Material.Succeeded())
		{
			ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
		}
		ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
		ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}

	//�浹ü 3�� �ڿ� �����
	InitialLifeSpan = 3.0f;
	
}

// Called when the game starts or when spawned
void AYReynaile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYReynaile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//�浹ü�� �߻�Ǿ��� �� ó�� ���ư��� ���� ����
	iledirection = GetActorForwardVector();
	SetActorLocation(GetActorLocation() + iledirection * yReynaileMoveCompSpeed * DeltaTime);

}

//�浹ü�� ���𰡿� �浹���� �� ����ϴ� ��
void AYReynaile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(yReynaileMoveComp->Velocity * 100.0f, Hit.ImpactPoint);
	}

	Destroy();
}