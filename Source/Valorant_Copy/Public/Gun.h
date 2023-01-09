// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gun.generated.h"


UCLASS()
class VALORANT_COPY_API AGun : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGun();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay);
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class USkeletalMeshComponent* Mesh1P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class USkeletalMeshComponent* FP_Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	float TimeBetweenShots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	float TimeReload=3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class UParticleSystem* MuzzleParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class UParticleSystem* ImpactParticles;

	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle_HandleRefire;
	FTimerHandle TimerHandle_Reload;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void StartFire();
	void StopFire();
	void FireShot();
	void ReloadInput();
	void Reload();

	//탄약
	int32 ammunition=25;

	//위젯 탄약불러오기
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetAmmo() { return ammunition;}


private:

	//데미지 선언
	UPROPERTY(EditAnywhere);
	float Damage = 10;

	FVector ShotDirection;
	//반동값
	FVector rebound=FVector(0,0,0);
	//반동 수직 상승 값 저장
	FVector reboundOrigin = FVector(0, 0, 0);
	//카메라 피치 값
	//FRotator CamPitch;

	//카메라 반동 횟수
	int32 recoilCount=0;
	//총 반동 횟수
	int32 reboundCount = 0;

	void Vertical(float AxisValue);
	void Horizontal(float AxisValue);

	//현재시간
	float currentTime;

	//발사여부
	bool isFire = false;

	float reZ;
	float reX;
	float reY;

	//카메라 방향 백터 변수
	FVector YDir;
	FVector ZDir;

};
