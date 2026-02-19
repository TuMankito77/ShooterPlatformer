// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

/**
 * 
 */
class LYRAGAME_API FEnemyDebugCategory : public FGameplayDebuggerCategory
{
	const float DEBUG_SPHERE_RADIUS = 50.0f;
	const int DEBUG_SPHERE_SEGMENTS = 12;

public:
	FEnemyDebugCategory();
	virtual void CollectData(APlayerController* Owner, AActor* DebugActor) override;
	virtual void DrawData(APlayerController* Owner, FGameplayDebuggerCanvasContext& CanvasContext) override;
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();

protected:
	FVector PatrolPointLocation;
	FVector AttackLocation;
	TObjectPtr<AActor> AttackTarget;
	bool bHasMoveTarget = false;
};
