// Copyright GameBox Studios All Rights Reserved.


#include "Enemy/Abilities/LyraGameplayAbility_EnemyDeath.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

void ULyraGameplayAbility_EnemyDeath::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	FGameplayCueParameters DeathGameplayCueParams;
	DeathGameplayCueParams.NormalizedMagnitude = TriggerEventData->EventMagnitude;
	DeathGameplayCueParams.RawMagnitude = TriggerEventData->EventMagnitude;
	DeathGameplayCueParams.EffectContext = TriggerEventData->ContextHandle;
	DeathGameplayCueParams.MatchedTagName = TriggerEventData->EventTag;
	DeathGameplayCueParams.OriginalTag = TriggerEventData->EventTag;
	DeathGameplayCueParams.AggregatedSourceTags = TriggerEventData->InstigatorTags;
	DeathGameplayCueParams.AggregatedTargetTags = TriggerEventData->TargetTags;
	DeathGameplayCueParams.Instigator = const_cast<AActor*>(TriggerEventData->Instigator.Get());
	DeathGameplayCueParams.SourceObject = TriggerEventData->Target;
	K2_ExecuteGameplayCueWithParams(DeathGameplayCueTag, DeathGameplayCueParams);

	GetWorld()->GetTimerManager().SetTimer(DeathDurationTimer, this, &ULyraGameplayAbility_EnemyDeath::OnDeathDurationTimerCompleted, DeathDuration, false);
	float MontagePlayRate = DeathMontage->GetPlayLength() / DeathDuration;

	if (IsValid(DeathMontage))
	{
		PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy
		(
			this,
			FName("DashAttackPlayMontage"),
			DeathMontage,
			MontagePlayRate,
			NAME_None,
			true,
			1.0F,
			0.0f
		);

		PlayMontageTask->ReadyForActivation();
	}
}

void ULyraGameplayAbility_EnemyDeath::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicatedEndAbility, bool bWasCancelled)
{
	if (IsValid(PlayMontageTask))
	{
		PlayMontageTask->EndTask();
	}

	if (DeathDurationTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(DeathDurationTimer);
	}
}

void ULyraGameplayAbility_EnemyDeath::OnDeathDurationTimerCompleted()
{
	const bool bReplicateEndAbility = true;
	const bool bWasCanceled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCanceled);
}
