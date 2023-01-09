// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Valorant.generated.h"

/**
 * 
 */
UCLASS()
class VALORANT_COPY_API AValorant : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	//���Ӹ�忡�� ����� �������Ʈ ������ �����Ѵ�
	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
		TSubclassOf<class UPlayerUI> playerUI;

	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
		int32 ammo=25;
};
