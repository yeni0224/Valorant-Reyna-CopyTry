// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Enemy.h"
#include "Engine/DamageEvents.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"

//#include "Components/SceneComponent.h"

// Sets default values
AGun::AGun()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_GUN"));
	FP_Gun->SetOnlyOwnerSee(true);
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("%s"), *FirstPersonCameraComponent->GetForwardVector().ToString());
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (isFire) {

		currentTime += DeltaTime;
		if (currentTime > TimeBetweenShots) {
			if (recoilCount < 7) {
				APawn::AddControllerPitchInput(-0.5f);
				recoilCount += 1;
				
			}
			else if (recoilCount <= 16) {
				APawn::AddControllerYawInput(-1);
				if (recoilCount % 2 == 0) {
					APawn::AddControllerPitchInput(-0.6f);
				}
				else if (recoilCount % 2 == 1) {
					APawn::AddControllerPitchInput(0.3f);
				}
				
				recoilCount += 1;
			}
			else if (recoilCount <= 25) {
				APawn::AddControllerYawInput(1);

				recoilCount += 1;
			}
			currentTime = 0;
		}

	}

}

// Called to bind functionality to input
void AGun::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &AGun::Vertical);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &AGun::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AGun::StartFire);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &AGun::StopFire);
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &AGun::ReloadInput);
	

	




}

void AGun::StartFire()
{
	//rebound = FVector(0,0,0);
	//rebound = FireShot(rebound);
	if (ammunition > 0) {
		isFire = true;
		GetWorldTimerManager().SetTimer(TimerHandle_HandleRefire, this, &AGun::FireShot, TimeBetweenShots, true);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("no ammo")));
	}
}

void AGun::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_HandleRefire);
	rebound = FVector(0,0,0);
	recoilCount = 0;
	reboundCount = 0;
	YDir = FVector(0, 0, 0);
	ZDir = FVector(0, 0, 0);
	isFire = false;
}

void AGun::FireShot()
{
	FHitResult Hit;

	//총의 탄퍼짐은 EndTrace로 조정
	//일정 패턴은 카메라 움직임으로 조정

	//카메라를 위로 올리는 반동
	//CamPitch = FirstPersonCameraComponent->GetRelativeRotation() + FRotator(10.0f, 0, 0);
	//FirstPersonCameraComponent->SetRelativeRotation(CamPitch);

	//총이 나가는 위치를 올리는 반동

	/*if (reboundCount <= 7) {
		reZ += FMath::RandRange(0.01f, 0.03f);
		rebound += FVector(0, 0, reZ);
		reboundCount++;
	}*/
	if (reboundCount == 7) {
		reboundOrigin = rebound;
	}
	
	//7발 까지는 패턴이 일정하다
	switch (reboundCount) {
	case 0:
		YDir = FirstPersonCameraComponent->GetRightVector() * 0;
		rebound *= 0;
		reboundCount++;
		break;
	case 1:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(-0.01f, 0.01f);
		rebound.Z += FMath::RandRange(0.005f, 0.01f);
		reboundCount++;
		break;
	case 2:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(-0.01f, 0.01f);
		rebound.Z += FMath::RandRange(0.005f, 0.01f);
		reboundCount++;
		break;
	case 3:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(0.01f, 0.17f);
		rebound.Z += FMath::RandRange(0.05f, 0.06f);
		reboundCount++;
		break;
	case 4:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(0.01f, 0.02f);
		rebound.Z += FMath::RandRange(0.05f, 0.06f);
		reboundCount++;
		break;
	case 5:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(0.02f, 0.03f);
		rebound.Z += FMath::RandRange(0.05f, 0.06f);
		reboundCount++;
		break;
	case 6:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(0.03f, 0.04f);
		rebound.Z += FMath::RandRange(0.05f, 0.06f);
		reboundCount++;
		break;
	}
	if (reboundCount > 6) {
		//rebound = reboundOrigin;
		//reX = FMath::RandRange(0.1, 0.3);
		reY = FMath::RandRange(-0.05f, 0.05f);
		reZ = FMath::RandRange(-0.05f, 0.05f);
		YDir = FirstPersonCameraComponent->GetRightVector() * reY;
		ZDir = FirstPersonCameraComponent->GetUpVector() * reZ;
		//rebound+=FVector(reX, reY, reZ);
		reboundCount++;
	}
	
	const float WeaponRange = 20000.0f;
	const FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation();
	const FVector EndTrace = (((FirstPersonCameraComponent->GetForwardVector()+rebound)+YDir+ZDir)* WeaponRange) + StartTrace;

	FCollisionQueryParams QueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(WeaponTrace), false, this);  
	
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, QueryParams)) {

		if (ImpactParticles) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, FTransform(Hit.ImpactNormal.Rotation(), Hit.ImpactPoint));
			//데미지 이벤트
			ShotDirection = FirstPersonCameraComponent->GetForwardVector();
			ShotDirection.Normalize();

			//FDamageEvent dam;
			//FPointDamageEvent fdm;

			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);

			//AActor* HitActor = Hit.GetActor();
			//if (HitActor != nullptr) {
			//	HitActor->TakeDamage(Damage, DamageEvent);
			// }
		}

	}

	if (MuzzleParticles) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleParticles, FP_Gun->GetSocketTransform(FName("Muzzle")));
	}

	if (FireSound != nullptr) {
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (FireAnimation != nullptr) {

		UAnimInstance* Animinstance = Mesh1P->GetAnimInstance();
		if (Animinstance != nullptr) {
			Animinstance->Montage_Play(FireAnimation, 1.f);
		}
	}
	
	
	//탄약이 0 이되면 사격종료
	ammunition--;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(" %d, isFrie? = %d"), ammunition, isFire));

	if (ammunition <= 0) {
		StopFire();
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("no ammo")));
	}

}

void AGun::Vertical(float AxisValue) {
	//direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	//direction.Normalize();
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AGun::Horizontal(float AxisValue) {
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AGun::ReloadInput() {
	if (isFire == false) {
		GetWorldTimerManager().SetTimer(TimerHandle_Reload, this, &AGun::Reload, TimeReload, false);
	}
}

void AGun::Reload()
{
	ammunition = 25;
}
