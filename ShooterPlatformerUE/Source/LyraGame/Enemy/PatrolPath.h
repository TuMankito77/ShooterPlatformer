// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPath.generated.h"

class USplineComponent;
class UBillboardComponent;

UCLASS()
class LYRAGAME_API APatrolPath : public AActor
{
	GENERATED_BODY()
	
public:
	TArray<FVector> PatrolPointLocations;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UBillboardComponent> PathVisial = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<USplineComponent> PatrolPoints = nullptr;

public:	
	APatrolPath(const FObjectInitializer& ObjectInitializer);
	virtual void PostInitializeComponents() override;
	int GetPatrolPointsLength();
	FVector GetPatrolPointLocation(int Index);

#if WITH_EDITOR

	UFUNCTION(CallInEditor, Category = "Enemy Debug")
	void ShowPatrolPointsInLevel();

#endif
};
