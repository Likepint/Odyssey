#include "Components/CComponentBase.h"
#include "Characters/CCharacterBase.h"

UCComponentBase::UCComponentBase()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCComponentBase::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACCharacterBase>(GetOwner());
}

void UCComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
