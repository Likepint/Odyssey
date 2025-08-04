#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CItem.generated.h"

class UTexture2D;

/**
 *	게임에 존재하는 모든 아이템의 최상위 부모 클래스
 *	인벤토리 UI에 표시될 이름, 아이콘 등 공통 데이터 소유
 */
UCLASS(Blueprintable)
class ODYSSEY_API UCItem : public UObject
{
	GENERATED_BODY()

public:
	// 아이템 이름 (UI에 표시)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText ItemName;

	// 인벤토리 아이콘 (UI에 표시)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UTexture2D> Icon;
};
