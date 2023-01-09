// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class VALORANT_COPY_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//�ڽ� �浹ü ������Ʈ
	UPROPERTY(EditAnywhere)
		class UBoxComponent* BoxComp;
	//����ƽ �޽� ������Ʈ
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* meshComp;

	//�ӷº���
	UPROPERTY(EditAnywhere)
		float moveSpeed = 500;

private:
	float h;
	float v;

	void moveHorizontal(float value);
	void moveVertical(float value);

};