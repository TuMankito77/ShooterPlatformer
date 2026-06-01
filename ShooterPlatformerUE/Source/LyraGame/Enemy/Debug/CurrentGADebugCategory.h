// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

/**
 *
 */
class LYRAGAME_API FCurrentGADebugCategory : public FGameplayDebuggerCategory
{
	public:
		static TWeakObjectPtr<AActor> CurrentDebugActor;
		FCurrentGADebugCategory();
		virtual void CollectData(APlayerController* Owner, AActor* DebugActor) override;
		virtual void OnDeactivated();
		static TSharedRef<FGameplayDebuggerCategory> MakeInstance();
};
