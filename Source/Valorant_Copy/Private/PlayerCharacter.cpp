// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//�ڽ� �ݶ��̴� ������Ʈ ����
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component")); //�����ڷ� �ݸ���
	//������ �ڽ� �ݶ��̴� ������Ʈ�� �ֻ�� ������Ʈ�� �����Ѵ�
	SetRootComponent(BoxComp);
	//����ƽ �޽� ������Ʈ�� �����Ѵ�
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));
	//�ڽ� �ݶ��̴� ������Ʈ�� �ڽ� ������Ʈ�� �����Ѵ�
	meshComp->SetupAttachment(BoxComp);
	//�ڽ� �ݶ��̴��� ũ�⸦ 50 50 50���� �����Ѵ�
	FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
	BoxComp->SetBoxExtent(boxSize);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//������� �Է�Ű �̿�
	//1.���� �Է°��� �¿� �Է°��� �̿��ؼ� ������͸� �����.
	FVector dir = FVector(0, h, v);

	//2. ��������� ���̰� 1�� �ǵ��� ����ȭ �Ѵ�.
	dir.Normalize();

	//3.�̵��� ��ġ ��ǥ�� ���Ѵ�(p=p0+vt)
	FVector nowLocation = GetActorLocation() + dir * moveSpeed * DeltaTime;

	//4.���� ������ ��ġ ��ǥ�� �տ��� ���� �� ��ǥ�� �����Ѵ�.
	SetActorLocation(nowLocation);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Axis ���ε��� ���� �Լ��� �����Ѵ�.
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerCharacter::moveHorizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerCharacter::moveVertical);

}

void APlayerCharacter::moveHorizontal(float value) {
	h = value;
}

void APlayerCharacter::moveVertical(float value) {
	v = value;
}

