// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimationSetUpComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LYRAGAME_API UAnimationSetUpComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UAnimInstance> DefaultAnimLayer = nullptr;

public:
	UAnimationSetUpComponent();
	void UpdateLinkedAnimClassLayer(TSubclassOf<UAnimInstance> AnimLayer);
	TSubclassOf<UAnimInstance> GetDefaultAnimLayer() { return DefaultAnimLayer; }
};
