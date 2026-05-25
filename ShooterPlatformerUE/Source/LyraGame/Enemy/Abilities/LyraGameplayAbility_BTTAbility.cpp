// Copyright GameBox Studios All Rights Reserved.


#include "Enemy/Abilities/LyraGameplayAbility_BTTAbility.h"
#include "Enemy/BaseEnemy.h"

ULyraGameplayAbility_BTTAbility::ULyraGameplayAbility_BTTAbility()
{
}

void ULyraGameplayAbility_BTTAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	AActor* OwningActor = GetAvatarActorFromActorInfo();

	if (!IsValid(OwningActor))
	{
		return;
	}

	ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(OwningActor);

	if (!IsValid(BaseEnemy))
	{
		return;
	}
	
	BaseEnemy->OnAbilityExecutionFinished.Broadcast();
}