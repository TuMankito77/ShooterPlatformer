// Copyright GameBox Studios All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyWidget.generated.h"

UCLASS()
class LYRAGAME_API UEnemyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnInitialize(AActor* WidgetOwner);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeinitialize(AActor* WidgetOwner);
};
