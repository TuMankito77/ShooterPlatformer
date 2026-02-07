// Copyright GameBox Studios All Rights Reserved.


#include "Enemy/AnimationSetUpComponent.h"

UAnimationSetUpComponent::UAnimationSetUpComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAnimationSetUpComponent::UpdateLinkedAnimClassLayer(TSubclassOf<UAnimInstance> AnimLayer)
{
	AActor* Owner = GetOwner();

	if (!IsValid(Owner))
	{
		return;
	}

	USkeletalMeshComponent* SkeletalMeshComponent = Owner->GetComponentByClass<USkeletalMeshComponent>();

	if (!IsValid(SkeletalMeshComponent))
	{
		return;
	}

	SkeletalMeshComponent->LinkAnimClassLayers(AnimLayer);
}
