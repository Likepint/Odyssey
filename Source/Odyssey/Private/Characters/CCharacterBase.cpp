#include "Characters/CCharacterBase.h"

ACCharacterBase::ACCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Init();
}

void ACCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACCharacterBase::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACCharacterBase::Init()
{
	// 캐릭터 메시의 기본 위치와 회전 설정
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void ACCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}
