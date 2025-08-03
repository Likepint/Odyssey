#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enums/ECharacterType.h"
#include "CCharacterAsset.generated.h"

USTRUCT(BlueprintType)
struct FCharacterAppearance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	USkeletalMesh* SkeletalMesh;

	// 필요하다면 여기에 애니메이션 블루프린트, 재질 등을 추가 가능
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<UAnimInstance> AnimBlueprint;
};

UCLASS()
class ODYSSEY_API UCCharacterAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FCharacterAppearance CharacterAppearances[(int32)ECharacterType::Max];
};
