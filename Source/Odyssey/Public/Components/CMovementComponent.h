#pragma once

#include "CoreMinimal.h"
#include "Components/CComponentBase.h"
#include "CMovementComponent.generated.h"

class UEnhancedInputComponent;
class UInputAction;
struct FInputActionValue;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ODYSSEY_API UCMovementComponent : public UCComponentBase
{
	GENERATED_BODY()

public:
	UCMovementComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	// 캐릭터가 호출할 입력 바인딩 함수
	virtual void SetupPlayerInput(UEnhancedInputComponent* PlayerInputComponent) override;

	void Move() { bCanMove = true; }
	void Stop() { bCanMove = false; }
	bool CanMove() const { return bCanMove; }

	bool WantsToStop() const { return bWantsToStop; }
	float GetSpeedAtStop() const { return SpeedAtStop; }

	void CheckStopSpeed();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Movement;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Crouch;

	bool bCanMove = true;
	
	bool bWantsToStop = false;
	float SpeedAtStop = 0.0f;

	void OnMovement(const FInputActionValue& InValue);
	void OnLook(const FInputActionValue& InValue);
	void OnCrouch(const FInputActionValue& InValue);
};
