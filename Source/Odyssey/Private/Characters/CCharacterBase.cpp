#include "Characters/CCharacterBase.h"

ACCharacterBase::ACCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACCharacterBase::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
}

void ACCharacterBase::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}
