// Copyright GameBox Studios All Rights Reserved.


#include "Enemy/Abilities/LyraGameplayAbility_DashAttack.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"
#include "GameFramework/RootMotionSource.h"
#include "LyraGame/AbilitySystem/LyraAbilitySystemComponent.h"

void ULyraGameplayAbility_DashAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UE_LOG(LogTemp, Display, TEXT("Excecuting Ability!"));

	RootMotionTask = UAbilityTask_ApplyRootMotionConstantForce::ApplyRootMotionConstantForce
	(
		this,
		FName("DashAttackRootMontion"),
		GetAvatarActorFromActorInfo()->GetActorForwardVector(),
		Streength,
		Duration,
		true,
		nullptr,
		ERootMotionFinishVelocityMode::SetVelocity,
		FVector(0, 0, 0),
		0,
		false
	);

	RootMotionTask->OnFinish.AddDynamic(this, &ULyraGameplayAbility_DashAttack::OnRootMotionTaskFinished);
}

void ULyraGameplayAbility_DashAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if(IsValid(RootMotionTask))
	{
		RootMotionTask->EndTask();
	}
}

void ULyraGameplayAbility_DashAttack::OnRootMotionTaskFinished()
{
	const bool bReplicateEndAbility = true;
	const bool bWasCanceled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCanceled);
}