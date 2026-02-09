// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DetourCrowdAIController.h"
#include "AIControllerBaseEnemy.generated.h"

class ABaseEnemy;

UCLASS()
class LYRAGAME_API AAIControllerBaseEnemy : public ADetourCrowdAIController
{
	GENERATED_BODY()
	
protected:
	TObjectPtr<ABaseEnemy> BaseEnemy;

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
