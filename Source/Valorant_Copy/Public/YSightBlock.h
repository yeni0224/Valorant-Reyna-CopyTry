// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YSightBlock.generated.h"

UCLASS()
class VALORANT_COPY_API AYSightBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYSightBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EyeshotSettings)
		class USphereComponent* sphereComp3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EyeshotSettings)
		class UStaticMeshComponent* meshComp3;

		class AYCEyeshot* eyeShotSkill;

		

private:

	void DestroySelf();
};
