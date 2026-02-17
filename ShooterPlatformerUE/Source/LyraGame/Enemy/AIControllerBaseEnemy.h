// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DetourCrowdAIController.h"
#include "AIControllerBaseEnemy.generated.h"

class ABaseEnemy;
class UAIPerceptionComponent;

UCLASS()
class LYRAGAME_API AAIControllerBaseEnemy : public ADetourCrowdAIController
{
	GENERATED_BODY()

public:
	AAIControllerBaseEnemy(const FObjectInitializer& ObjectInitializer);
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent = nullptr;
	
	TObjectPtr<ABaseEnemy> BaseEnemy = nullptr;

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
