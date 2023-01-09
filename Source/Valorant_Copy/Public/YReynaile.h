// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "YReynaile.generated.h"

UCLASS()
class VALORANT_COPY_API AYReynaile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYReynaile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Projectile class to spawn
	TSubclassOf<class YReynaile> YReynaileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//���� ���� : 
	//���� ���ӿ� �߻�ü ���⸦ �����ϴ� ���� �����̴�
	//����ź ���� �߻�ü�� ���α׷����Ͽ� ȭ�� �߾ӿ��� ��� ����� �浹�� ������ ���ư����� �� ��

	//Called to bind functionality to input
	//virtual void SetupPlayerInputComponent (class UInputComponent* YReynaInputComponent) override;

	//�浹ü�� ���𰡿� �浹���� �� ����ϴ� ��
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	// Sphere collision component(������ �浹ü ����)
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComp;

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* yReynaileMoveComp;

	//Projectile Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UStaticMeshComponent* ProjectileMeshComponent;

	//Projectile Material
	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
	UMaterialInstanceDynamic* ProjectileMaterialInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BulletSettings)
	float yReynaileMoveCompSpeed = 4500.0f;

	//�浹ü�� �߻�Ǿ��� �� ó�� ���ư��� ���� ����
	//void FireDirection(const FVector& ShootDirection);

private:
	FVector iledirection;

};
