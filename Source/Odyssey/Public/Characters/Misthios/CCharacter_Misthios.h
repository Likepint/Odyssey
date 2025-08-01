#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacterBase.h"
#include "Enums/ECharacterType.h"
#include "CCharacter_Misthios.generated.h"

class UCharacterData;

class UInputMappingContext;

class USpringArmComponent;
class UCameraComponent;

class UCMovementComponent;

UCLASS(Blueprintable)
class ODYSSEY_API ACCharacter_Misthios : public ACCharacterBase
{
	GENERATED_BODY()

public:
	ACCharacter_Misthios();
	
	// OnConstruction은 에디터에서 액터의 프로퍼티가 변경될 때마다 호출
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

protected:
	// 에디터에서 캐릭터 외형 데이터 애셋을 지정할 수 있도록 프로퍼티 추가
	UPROPERTY(EditAnywhere, Category = "CharacterData")
	UCharacterData* CharacterDataAsset;

	// 에디터에서 알렉시오스/카산드라를 선택할 수 있는 옵션
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "CharacterType", meta = (AllowPrivateAccess = "true"))
	ECharacterType CharacterType = ECharacterType::Alexios;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> IMC_Misthios;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCMovementComponent> MovementComponent;
	
	virtual void Init() override;
	
	virtual void BeginPlay() override;
};
