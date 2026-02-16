// Copyright GameBox Studios All Rights Reserved.
#include "Enemy/Debug/EnemyDebugCategory.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

FEnemyDebugCategory::FEnemyDebugCategory()
{
	bShowOnlyWithDebugActor = true;
}

void FEnemyDebugCategory::CollectData(APlayerController* Owner, AActor* DebugActor)
{
	bHasMoveTarget = false;

	if (!IsValid(DebugActor))
	{
		return;
	}

	AAIController* AIController = Cast<AAIController>(DebugActor->GetInstigatorController());

	if (!IsValid(AIController))
	{
		return;
	}

	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();

	if (!IsValid(BlackboardComponent))
	{
		return;
	}

	TargetLocation = BlackboardComponent->GetValueAsVector("TargetLocation");
	bHasMoveTarget = true;
}

void FEnemyDebugCategory::DrawData(APlayerController* Owner, FGameplayDebuggerCanvasContext& CanvasContext)
{
	if (bHasMoveTarget)
	{
		DrawDebugSphere(Owner->GetWorld(), TargetLocation, 50.0f, 12, FColor::Blue, false, 1);
		CanvasContext.Printf(TEXT("Current Target Location: %s"), *TargetLocation.ToString());
	}
	else
	{
		CanvasContext.Printf(TEXT("Current Target Location: None"));
	}
}

TSharedRef<FGameplayDebuggerCategory> FEnemyDebugCategory::MakeInstance()
{
	return MakeShareable(new FEnemyDebugCategory());
}