// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/LyraGameplayAbility.h"
#include "LyraGameplayAbility_BTTAbility.generated.h"

/**
 * 
 */
UCLASS()
class LYRAGAME_API ULyraGameplayAbility_BTTAbility : public ULyraGameplayAbility
{
	GENERATED_BODY()

public:
	ULyraGameplayAbility_BTTAbility();

protected:
	bool IsDebugginEnabled();
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
