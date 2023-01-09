// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YCEyeshot.generated.h"

UCLASS()
class VALORANT_COPY_API AYCEyeshot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYCEyeshot();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EyeshotSettings)
		class USphereComponent* sphereComp2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EyeshotSettings)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EyeshotSettings)
		float eyeshotSpeed = 1000.f;

	//���� ��ġ�� �˰� �����ؾ��ϱ� ������ ���� ����
	UPROPERTY(EditDefaultsOnly, Category = EyeshotSettings)
		class UParticleSystem* Explosion_effect;

	//��������Ʈ�θ��� �Լ��� UFUNCTION���� ����
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
		TSubclassOf<class AYSightBlock> sightBlock;

	bool isEyeshot = true;
	bool bIsSpawnSightBlock = false;

private:
	FVector direction;
	FTimerHandle lifeTimer;
	
	float eyeshotDistance = 0;

	UFUNCTION()
	void DestroySelf();

	

	UFUNCTION()
	void SpawnSightBlock();


};
