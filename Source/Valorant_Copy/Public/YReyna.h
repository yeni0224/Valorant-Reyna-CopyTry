// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include"Components/CapsuleComponent.h"
#include "YReynaile.h"
#include "YReyna.generated.h"

UCLASS()
class VALORANT_COPY_API AYReyna : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AYReyna();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//YReynaile 연결하기 위한(?)
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AYReynaile> ProjectileClass;

private:

	//좌우 회전 입력 처리
	void TurnRight(float AxisValue);
	//상하 회전 입력 처리
	void Lookup(float AxisValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//UCamera Component 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		class UCameraComponent* yReynaCamComp;

	//1인칭 카메라 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;

	//이동속도
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
		float walkSpeed = 600.0f;

	//캐릭터 이동방향
	FVector Reynadirection;

	//좌우이동 입력 이벤트 처리 함수
	void InputHorizontal(float value);

	//상하 이동 입력 이벤트 처리 함수
	void InputVertical(float value);

	//점프 입력 이벤트 처리 함수
	void InputJump();

	//총 skeletalMesh
	UPROPERTY(VisibleAnywhere, Category = GunMesh)
	class USkeletalMeshComponent* gunMeshComp;

	//총알 장전
	void BulletLoad();

	//Crouch
	void InputCrouch();

	//Fire
	UFUNCTION()
	void Fire();

	//총알 파편 효과
	UPROPERTY(EditAnywhere, Category = BluePrintEffect)
		class UParticleSystem* bulletEffectFactory;
	
	
	/*스킬*/

	//눈총 스킬 EyeshotSkill
	void EyeShotSkill();
// 	UPROPERTY(EditAnywhere, Category = "Collision")
// 	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

	UPROPERTY(EditAnywhere, Category = EyeshotSettings)
	TSubclassOf<class AYCEyeshot> eyeShot;

	//포식 스킬 Predator
	void PredatorSkill();
	UPROPERTY(EditAnywhere, Category = EyeshotSettings)
	TSubclassOf<class AYQPredator> predator;

		

	//카메라 위치로부터 총구의 위치를 잡는다(?)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	//SilentStep
	void SilentStep();


	//TelescopeSight 조준경
	void TelescopeSight();

	//조준경 활성화 여부
	bool bTelescopeAim = false;

	//조준경UI 위젯공장
	UPROPERTY(EditAnywhere, Category = TelescopeUI)
		TSubclassOf<class UUserWidget> telescopeFactory;

	//조준경UI 위젯 인스턴스
	class UUserWidget* _scopeUI;

	//무기고 오픈
	void WeaponStorageOpen();

private:
	class AYReyna* ytarget;


};
