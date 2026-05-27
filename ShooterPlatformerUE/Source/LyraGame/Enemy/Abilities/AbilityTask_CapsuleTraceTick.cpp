// Copyright GameBox Studios All Rights Reserved.


#include "Enemy/Abilities/AbilityTask_CapsuleTraceTick.h"

UAbilityTask_CapsuleTraceTick::UAbilityTask_CapsuleTraceTick()
{
	bTickingTask = true;
}

void UAbilityTask_CapsuleTraceTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (!IsValid(Ability))
	{
		EndTask();
		return;
	}

	AActor* OwningActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
}