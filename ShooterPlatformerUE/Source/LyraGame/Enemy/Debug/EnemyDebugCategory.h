// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

/**
 * 
 */
class LYRAGAME_API FEnemyDebugCategory : public FGameplayDebuggerCategory
{
public:
	FEnemyDebugCategory();
	virtual void CollectData(APlayerController* Owner, AActor* DebugActor) override;
	virtual void DrawData(APlayerController* Owner, FGameplayDebuggerCanvasContext& CanvasContext) override;
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();
protected:
	FVector TargetLocation;
	bool bHasMoveTarget = false;
};
