// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YBullet.generated.h"

UCLASS()
class VALORANT_COPY_API AYBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 발사체의 이동을 담당할 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Movement)
	class UProjectileMovementComponent* movementComp;

	//충돌 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Movement)
	class USphereComponent* collisionComp;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	class UStaticMeshComponent* bodyMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BulletSettings)
	float moveSpeed = 4500.f;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	FVector direction;	
	FTimerHandle lifeTimer;

	void DestroyMySelf();

};
