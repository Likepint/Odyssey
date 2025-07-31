#include "Components/CMovementComponent.h"
#include "Characters/CCharacterBase.h"
#include "EnhancedInputComponent.h"

UCMovementComponent::UCMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCMovementComponent::SetupPlayerInput(UEnhancedInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	if (IA_Movement)
		PlayerInputComponent->BindAction(IA_Movement, ETriggerEvent::Triggered, this, &UCMovementComponent::OnMovement);

	if (IA_Look)
		PlayerInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &UCMovementComponent::OnLook);

	if (IA_Crouch)
		PlayerInputComponent->BindAction(IA_Crouch, ETriggerEvent::Started, this, &UCMovementComponent::OnCrouch);
}

void UCMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCMovementComponent::OnMovement(const FInputActionValue& InValue)
{
	const FVector2D inputAxisVector = InValue.Get<FVector2D>();

	const FRotator rotation = OwnerCharacter->GetControlRotation();
	const FRotator yawRotation(0.f, rotation.Yaw, 0.f);

	// 컨트롤러 방향을 기준으로 Forward와 Right 벡터 계산
	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	OwnerCharacter->AddMovementInput(forwardDirection, inputAxisVector.X);
	OwnerCharacter->AddMovementInput(rightDirection, inputAxisVector.Y);
}

void UCMovementComponent::OnLook(const FInputActionValue& InValue)
{
	const FVector2D inputAxisVector = InValue.Get<FVector2D>();

	// 좌우 회전(Yaw)
	OwnerCharacter->AddControllerYawInput(inputAxisVector.X);

	// 상하 회전(Pitch)
	OwnerCharacter->AddControllerPitchInput(inputAxisVector.Y);
}

void UCMovementComponent::OnCrouch(const FInputActionValue& InValue)
{
	if (OwnerCharacter->bIsCrouched)
		OwnerCharacter->UnCrouch();
	else OwnerCharacter->Crouch();
}
