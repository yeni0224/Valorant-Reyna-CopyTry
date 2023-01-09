// Fill out your copyright notice in the Description page of Project Settings.


#include "Valorant.h"
#include "PlayerUI.h"

void AValorant::BeginPlay()
{
	//������ ������ �����������Ʈ�� �ν��Ͻ�ȭ ��Ų��   ������ �������
	UPlayerUI* player_UI = CreateWidget<UPlayerUI>(GetWorld(), playerUI);

	//�ν��Ͻ�ȭ ��Ų �����������Ʈ�� ����Ʈ�� �׸���
	if (player_UI != nullptr) {
		player_UI->AddToViewport();
	}

}
