#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

UCLASS()
class ODYSSEY_API ACAttachment : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAttachment();

	// 캐릭터의 특정 소켓에 이 액터를 부착시키는 함수
	void AttachToSocket(USceneComponent* InParent, FName InSocketName);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;
	
	virtual void BeginPlay() override;
};
