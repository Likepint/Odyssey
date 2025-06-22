#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacterBase.generated.h"

UCLASS(Abstract, NotBlueprintable)
class ODYSSEY_API ACCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACCharacterBase();

	virtual void Tick(float DeltaTime) override;

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
};
