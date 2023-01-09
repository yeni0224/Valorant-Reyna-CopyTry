// Fill out your copyright notice in the Description page of Project Settings.


#include "YReyna.h"
#include <GameFramework/SpringArmComponent.h> //SpringArm Component 등록
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "YCEyeshot.h"
#include "YQPredator.h"
#include "CollisionQueryParams.h"
#include <Camera/CameraComponent.h> //UCamera Component 등록


// Sets default values
AYReyna::AYReyna()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//1. 스켈레탈메시 데이터를 불러온다
	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		TempMesh(TEXT("SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'"));

	
		//1인칭 시점으로 보이는 카메라 컴포넌트 생성
		yReynaCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
		check(yReynaCamComp != nullptr);

		//캡슐컴포넌트에 카메라 컴포넌트 붙이기
		yReynaCamComp->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

		//카메라 위치 눈높이쯤 맞추기
		//yReynaCamComp->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));

		//카메라 회전을 pawn이 컨트롤 할 수 있도록
		yReynaCamComp->bUsePawnControlRotation = true;

		//1인칭 매시컴포넌트(플레이 당사자용) 생성
		FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
		check(FPSMesh != nullptr);

		//플레이하는 당사자만 1인칭시점의 손을 볼 수 있도록
		FPSMesh->SetOnlyOwnerSee(true);

		//FpsMesh와 Fps camera 연결하기
		FPSMesh->SetupAttachment(yReynaCamComp);

		//1인칭 mesh가 그림자 지지 않도록
		FPSMesh->bCastDynamicShadow = false;
		FPSMesh->CastShadow = false;

		//플레이 당사자가 3인칭 캐릭터매시는 안보이도록
		GetMesh()->SetOnlyOwnerSee(true);

	if (TempMesh.Succeeded())
	{

		//4. 총 skeletalMesh 컴포넌트 등록
		gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComp"));

		//4-1. 부모 컴포넌트를 Mesh컴포넌트로 설정
		gunMeshComp->SetupAttachment(GetMesh());

		//4-2. 스켈레탈메시 데이터 로드
		ConstructorHelpers::FObjectFinder<USkeletalMesh> TempGunMesh(TEXT("SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));

		//4-3. 데이터 로드가 성공했다면
		if (TempGunMesh.Succeeded())
		{
		//4-4. 스켈레탈메시 데이터 할당
		gunMeshComp->SetSkeletalMesh(TempGunMesh.Object);

		//4-5. 위치 조정하기
		gunMeshComp->SetRelativeLocationAndRotation((FVector(-59.3f, 3.34f, 94.86f)), FRotator(0, 0, 90.f));
		}
	}

}

// Called when the game starts or when spawned
void AYReyna::BeginPlay()
{
	Super::BeginPlay();


	
}

// Called every frame
void AYReyna::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//플레이어 이동처리
	Reynadirection.Normalize();
	FVector dir = GetActorLocation() + Reynadirection * walkSpeed * DeltaTime;
	SetActorLocation(dir);
	
}


// Called to bind functionality to input
void AYReyna::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//시야 회전처리 하는 함수를 키보드 설정(키맵핑)과 묶어주는 것
	PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &AYReyna::TurnRight);
	PlayerInputComponent->BindAxis(TEXT("Lookup"), this, &AYReyna::Lookup);

	//(ADWS)키보드 입력함수 바인딩
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &AYReyna::InputHorizontal);	
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &AYReyna::InputVertical);

	//점프 입력 바인딩
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AYReyna::InputJump);

	//Reload 바인딩
	PlayerInputComponent->BindAction(TEXT("BulletLoad"), IE_Pressed, this, &AYReyna::BulletLoad);

	//Crouch 바인딩
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AYReyna::InputCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AYReyna::InputCrouch);

	//Fire 바인딩
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AYReyna::Fire);

	//EyeShot Skill 눈총스킬 키보드 C 연결
	PlayerInputComponent->BindAction(TEXT("EyeShotSkill"), IE_Pressed, this, &AYReyna::EyeShotSkill);

	//Predator Skill 포식스킬 키보드 Q 연결
	PlayerInputComponent->BindAction(TEXT("PredatorSkill"), IE_Pressed, this, &AYReyna::PredatorSkill);

}

//시야 회전처리
void AYReyna::TurnRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AYReyna::Lookup(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

//캐릭터 양옆 움직임
void AYReyna::InputHorizontal(float value)
{
	Reynadirection.Y = value;

}

//캐릭터 상하 움직임
void AYReyna::InputVertical(float value)
{
	Reynadirection.X = value;
}

void AYReyna::InputJump()
{
	Jump();
}

void AYReyna::BulletLoad()
{

}

void AYReyna::InputCrouch()
{

}

void AYReyna::Fire() 
{
    //만들어준 YReynaile의 ProjectileClass에 접근할것이다.
	if (ProjectileClass) 
	{
		//카메라 위치 잡기
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation); //눈높이설정(?)

		//카메라 앞에서의 총구(Muzzle) 위치를 대략적으로 설정한다
		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

		//카메라 앞에 세워둘 총구의 위치를 world로(world location 같은 느낌인듯)
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation). TransformVector(MuzzleOffset);

		//Skew the aim to be slightly upwards(위쪽으로 살짝 비스듬히 조절하라?) Skew : 비스듬히 움직이다
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;

		//UWorld* World = GetWorld(); 
		//얜 왜쓰는지 모르겠지만 일단 주석으로 박고 함수 자체를 사용하여 접근할것이다 
		//GetWorld()-> 이렇게 사용해주면 된다.

		if (GetWorld()) 
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator(); 
			
			//instigator을 가해자로 생각할 것.
			//내가 몬스터를 화살로 공격한다 >> instigator가 나(캐릭터가 발생시킨 가해자)

			AYReynaile* Projectile = GetWorld()->SpawnActor<AYReynaile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

			//if (Projectile) {

				//projectile(충돌체(?))의 궤적 설정하기 (Set the projectile's initial trajectory)
				FVector LaunchDirection = MuzzleRotation.Vector();

				//레이나의 방향으로 총을 발사하는 궤적을 지정할것이다
				//(AYReyna::Projectile)->(AYReynaile::iledirection(LaunchDirection));
			//}
			
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Firebullet is Working"));
}

void AYReyna::EyeShotSkill() {

	

	if (ProjectileClass)
	{
		//카메라 위치 잡기
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation); //눈높이설정(?)

		//카메라 앞에서의 총구(Muzzle) 위치를 대략적으로 설정한다
		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

		//카메라 앞에 세워둘 총구의 위치를 world로(world location 같은 느낌인듯)
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		//Skew the aim to be slightly upwards(위쪽으로 살짝 비스듬히 조절하라?) Skew : 비스듬히 움직이다
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;


		if (GetWorld())
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			//instigator을 가해자로 생각할 것.
			//내가 몬스터를 화살로 공격한다 >> instigator가 나(캐릭터가 발생시킨 가해자)
						
			AYCEyeshot* Projectile = GetWorld()->SpawnActor<AYCEyeshot>(eyeShot, MuzzleLocation, MuzzleRotation, SpawnParams);

			//if (Projectile) {

				//projectile(충돌체(?))의 궤적 설정하기 (Set the projectile's initial trajectory)
			FVector LaunchDirection = MuzzleRotation.Vector();

			//레이나의 방향으로 총을 발사하는 궤적을 지정할것이다
			//(AYReyna::Projectile)->(AYReynaile::iledirection(LaunchDirection));
		     //}

			Projectile->bIsSpawnSightBlock = true;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("EyeshotSkill is Working"));
}

void AYReyna::PredatorSkill() {

	if (ProjectileClass)
	{
		//카메라 위치 잡기
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation); //눈높이설정(?)

		//카메라 앞에서의 총구(Muzzle) 위치를 대략적으로 설정한다
		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

		//카메라 앞에 세워둘 총구의 위치를 world로(world location 같은 느낌인듯)
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		//Skew the aim to be slightly upwards(위쪽으로 살짝 비스듬히 조절하라?) Skew : 비스듬히 움직이다
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;

		

		if (GetWorld())
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			//instigator을 가해자로 생각할 것.
			//내가 몬스터를 화살로 공격한다 >> instigator가 나(캐릭터가 발생시킨 가해자)

			AYQPredator* Projectile = GetWorld()->SpawnActor<AYQPredator>(predator, MuzzleLocation, MuzzleRotation, SpawnParams);

			//if (Projectile) {

				//projectile(충돌체(?))의 궤적 설정하기 (Set the projectile's initial trajectory)
			FVector LaunchDirection = MuzzleRotation.Vector();

			//레이나의 방향으로 총을 발사하는 궤적을 지정할것이다
			//(AYReyna::Projectile)->(AYReynaile::iledirection(LaunchDirection));
		//}

		}
	}
	UE_LOG(LogTemp, Warning, TEXT("PredatorSkill is Working"));
}

void AYReyna::SilentStep()
{

}

void AYReyna::TelescopeSight() {

	// 	if (bTelescopeAim) {
	// 		return;
	// 	}
	// 
	// 	//Pressed 입력처리
	// 	if (bTelescopeAim = false) {
	// 
	// 		//1. 조준경 활성화
	// 		bTelescopeAim = true;
	// 
	// 		//2.조준경 UI 등록
	// 		_scopeUI->AddToViewport();
	// 
	// 		//3. 카메라 시야각 Field of View 설정
	// 		yReynaCamComp->SetFieldOfView(45.0f);
	// 	}
	// 	
	// 	//Released 입력처리
	// 	else {
	// 	    //1. 조준경 비활성화
	// 		bTelescopeAim = false;
	// 
	// 		//2.조준경 UI 해제
	// 		_scopeUI->RemoveFromViewport();
	// 
	// 		//3. 카메라 시야각 원래대로 복원
	// 		yReynaCamComp->SetFieldOfView(90.0f);
	// 	}

}

void AYReyna::WeaponStorageOpen()
{

}