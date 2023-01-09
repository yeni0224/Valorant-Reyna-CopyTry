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
		//충돌체를 표현하기 위해 구형을 사용한다
		CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

		//구형 충돌체 이름 설정
		CollisionComp->BodyInstance.SetCollisionProfileName(TEXT("YReynaile"));

		//충돌체가 충돌한 후 이벤트 호출하기
		CollisionComp->OnComponentHit.AddDynamic(this, &AYReynaile::OnHit);

		//Sphere(구형) 크기 설정
		CollisionComp->InitSphereRadius(15.0f);

		//충돌체를 루트컴포넌트로 설정
		RootComponent = CollisionComp;
	}

	if (!yReynaileMoveComp) 
	{
		//이 컴포넌트 움직임 컨트롤 설정하기
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

	//충돌체 3초 뒤에 지우기
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

	//충돌체가 발사되었을 때 처음 나아가는 슈팅 방향
	iledirection = GetActorForwardVector();
	SetActorLocation(GetActorLocation() + iledirection * yReynaileMoveCompSpeed * DeltaTime);

}

//충돌체가 무언가에 충돌했을 때 기능하는 것
void AYReynaile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(yReynaileMoveComp->Velocity * 100.0f, Hit.ImpactPoint);
	}

	Destroy();
}