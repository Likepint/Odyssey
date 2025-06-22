#include "Characters/Misthios/CCharacter_Misthios.h"

ACCharacter_Misthios::ACCharacter_Misthios()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACCharacter_Misthios::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACCharacter_Misthios::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
}

void ACCharacter_Misthios::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACCharacter_Misthios::BeginPlay()
{
	Super::BeginPlay();
}
