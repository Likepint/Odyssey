#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CComponentBase.generated.h"

class ACCharacterBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ODYSSEY_API UCComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UCComponentBase();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	TObjectPtr<ACCharacterBase> OwnerCharacter;
	
	virtual void BeginPlay() override;
};
