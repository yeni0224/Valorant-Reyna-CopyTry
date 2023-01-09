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

	//구현 목적 : 
	//슈팅 게임용 발사체 무기를 구현하는 것이 목적이다
	//수류탄 같은 발사체를 프로그래밍하여 화면 중앙에서 쏘고 세상과 충돌할 때까지 날아가도록 할 것

	//Called to bind functionality to input
	//virtual void SetupPlayerInputComponent (class UInputComponent* YReynaInputComponent) override;

	//충돌체가 무언가에 충돌했을 때 기능하는 것
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	// Sphere collision component(구형의 충돌체 생성)
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

	//충돌체가 발사되었을 때 처음 나아가는 슈팅 방향
	//void FireDirection(const FVector& ShootDirection);

private:
	FVector iledirection;

};
