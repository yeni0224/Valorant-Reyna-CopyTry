// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Jett.generated.h"




UCLASS()
class VALORANT_COPY_API AJett : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJett();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerSettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerSettings)
	class UStaticMeshComponent* meshComp;

	void Turn(float value);

	void LookUp(float value);

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float walkSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float runSpeed = 300.0f;

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float dashDistance = 3000.0f;

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float jumpdashDistance = 2000.0f;

	float xValue;
	float yValue;

	bool keepPressed;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SmokeGrenade;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Knife;

	class AKnife* knife0;
	class AKnife* knife1;
	class AKnife* knife2;
	class AKnife* knife3;
	class AKnife* knife4;
	class ASmokeGrenade* smoke;
	FTimerHandle KnifeTime;
	FTimerHandle KnifeTime1;
	FTimerHandle KnifeTime2;
	FTimerHandle KnifeTime3;

	TArray< AKnife*> knifeArray;

	

	int32 MaxKnife = 0;
	FVector DeactivatedLocation;
	FVector ActivatedLocation = GetActorLocation();

	FVector DashDir;

	FVector direction;
	

	UFUNCTION()
	void Horizontal(float value);
	UFUNCTION()
	void Vertical(float value);
	
	void InputJump ();

	void Walking();

	void WalkEnd();

	void JumpDash();

	void Dash();

	void Smoke();

	void SmokeControlEnd();

	void KnifeSetting();

	void Fire();

	void FireSp();
};
