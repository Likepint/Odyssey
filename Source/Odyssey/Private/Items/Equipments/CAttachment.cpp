#include "Items/Equipments/CAttachment.h"
#include "Global.h"

ACAttachment::ACAttachment()
{
	// Root
	CHelpers::CreateComponent<USceneComponent>(this, Root, TEXT("Root"));

	// SKeletalMesh
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, SkeletalMesh, TEXT("SkeletalMesh"), Root);
	SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACAttachment::AttachToSocket(USceneComponent* InParent, FName InSocketName)
{
	const FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);

	Super::AttachToComponent(InParent, rules, InSocketName);
}

void ACAttachment::BeginPlay()
{
	Super::BeginPlay();
}
