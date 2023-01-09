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

	//YReynaile �����ϱ� ����(?)
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AYReynaile> ProjectileClass;

private:

	//�¿� ȸ�� �Է� ó��
	void TurnRight(float AxisValue);
	//���� ȸ�� �Է� ó��
	void Lookup(float AxisValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//UCamera Component �߰�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		class UCameraComponent* yReynaCamComp;

	//1��Ī ī�޶� �߰�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;

	//�̵��ӵ�
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
		float walkSpeed = 600.0f;

	//ĳ���� �̵�����
	FVector Reynadirection;

	//�¿��̵� �Է� �̺�Ʈ ó�� �Լ�
	void InputHorizontal(float value);

	//���� �̵� �Է� �̺�Ʈ ó�� �Լ�
	void InputVertical(float value);

	//���� �Է� �̺�Ʈ ó�� �Լ�
	void InputJump();

	//�� skeletalMesh
	UPROPERTY(VisibleAnywhere, Category = GunMesh)
	class USkeletalMeshComponent* gunMeshComp;

	//�Ѿ� ����
	void BulletLoad();

	//Crouch
	void InputCrouch();

	//Fire
	UFUNCTION()
	void Fire();

	//�Ѿ� ���� ȿ��
	UPROPERTY(EditAnywhere, Category = BluePrintEffect)
		class UParticleSystem* bulletEffectFactory;
	
	
	/*��ų*/

	//���� ��ų EyeshotSkill
	void EyeShotSkill();
// 	UPROPERTY(EditAnywhere, Category = "Collision")
// 	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

	UPROPERTY(EditAnywhere, Category = EyeshotSettings)
	TSubclassOf<class AYCEyeshot> eyeShot;

	//���� ��ų Predator
	void PredatorSkill();
	UPROPERTY(EditAnywhere, Category = EyeshotSettings)
	TSubclassOf<class AYQPredator> predator;

		

	//ī�޶� ��ġ�κ��� �ѱ��� ��ġ�� ��´�(?)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	//SilentStep
	void SilentStep();


	//TelescopeSight ���ذ�
	void TelescopeSight();

	//���ذ� Ȱ��ȭ ����
	bool bTelescopeAim = false;

	//���ذ�UI ��������
	UPROPERTY(EditAnywhere, Category = TelescopeUI)
		TSubclassOf<class UUserWidget> telescopeFactory;

	//���ذ�UI ���� �ν��Ͻ�
	class UUserWidget* _scopeUI;

	//����� ����
	void WeaponStorageOpen();

private:
	class AYReyna* ytarget;


};
