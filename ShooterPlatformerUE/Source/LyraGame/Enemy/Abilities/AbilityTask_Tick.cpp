// Copyright GameBox Studios All Rights Reserved.


#include "Enemy/Abilities/AbilityTask_Tick.h"

void UAbilityTask_Tick::Activate()
{
	bTickingTask = true;
}

void UAbilityTask_Tick::OnDestroy(bool WasAbilityEnded)
{
	Super::OnDestroy(WasAbilityEnded);
}

void UAbilityTask_Tick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	OnTaskTick.Broadcast(DeltaTime);
}

UAbilityTask_Tick* UAbilityTask_Tick::CreateTickingAbilityTask(UGameplayAbility* OwningAbility)
{
	UAbilityTask_Tick* Task = NewAbilityTask<UAbilityTask_Tick>(OwningAbility);
	return Task;
}