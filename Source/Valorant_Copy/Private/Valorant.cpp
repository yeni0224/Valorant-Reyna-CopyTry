// Fill out your copyright notice in the Description page of Project Settings.


#include "Valorant.h"
#include "PlayerUI.h"

void AValorant::BeginPlay()
{
	//실제로 설정한 위젯블루프린트를 인스턴스화 시킨다   위젯은 월드소유
	UPlayerUI* player_UI = CreateWidget<UPlayerUI>(GetWorld(), playerUI);

	//인스턴스화 시킨 위젯블루프린트를 뷰포트에 그린다
	if (player_UI != nullptr) {
		player_UI->AddToViewport();
	}

}
