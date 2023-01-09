// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YQPredator.generated.h"

UCLASS()
class VALORANT_COPY_API AYQPredator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYQPredator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EyeshotSettings)
		class USphereComponent* sphereComp1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EyeshotSettings)
		class UStaticMeshComponent* meshComp1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EyeshotSettings)
		float predatorSpeed = 1000.f;

	//적의 위치를 알고 폭발해야하기 때문에 변수 생성
	UPROPERTY(EditDefaultsOnly, Category = EyeshotSettings)
		class UParticleSystem* Explosion_effect1;

	//델리게이트로만든 함수는 UFUNCTION으로 설정
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	FVector direction;
	FTimerHandle lifeTimer;

	float predatorDistance = 0;
	float currentTime = 0;

	void DestroySelf();

};
