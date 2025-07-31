#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CMisthiosController.generated.h"

UCLASS()
class ODYSSEY_API ACMisthiosController : public APlayerController
{
	GENERATED_BODY()

public:
	ACMisthiosController();

protected:
	virtual void BeginPlay() override;
};
