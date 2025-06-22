#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacterBase.h"
#include "CCharacter_Misthios.generated.h"

UCLASS(Blueprintable)
class ODYSSEY_API ACCharacter_Misthios : public ACCharacterBase
{
	GENERATED_BODY()

public:
	ACCharacter_Misthios();

	virtual void Tick(float DeltaTime) override;

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
};
