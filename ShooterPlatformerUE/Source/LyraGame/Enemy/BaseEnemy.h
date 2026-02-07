// All rights reserved to GameBox Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BaseEnemy.generated.h"

class ULyraAbilitySystemComponent;
class UAbilitySystemComponent;
class UAnimationSetUpComponent;

UCLASS()
class LYRAGAME_API ABaseEnemy : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAnimationSetUpComponent> AnimationSetUpComponent = nullptr;

public:

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	ULyraAbilitySystemComponent* GetLyraAbilitySystemComponent() const;

	ABaseEnemy(const FObjectInitializer& ObejectInitializer);
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<ULyraAbilitySystemComponent> AbilitySystemComponent = nullptr;
	virtual void SetStartingAnimationLayer();
};
