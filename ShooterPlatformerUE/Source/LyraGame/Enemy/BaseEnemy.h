// All rights reserved to GameBox Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BaseEnemy.generated.h"

class ULyraAbilitySystemComponent;
class UAbilitySystemComponent;
class UAnimationSetUpComponent;
class APatrolPath;
class ULyraAbilitySet;

UCLASS()
class LYRAGAME_API ABaseEnemy : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	TObjectPtr<UAnimationSetUpComponent> AnimationSetUpComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	TObjectPtr<UBehaviorTree> BehaviorTree = nullptr;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	TObjectPtr<APatrolPath> PatrolPath = nullptr;

public:

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	ULyraAbilitySystemComponent* GetLyraAbilitySystemComponent() const;

	ABaseEnemy(const FObjectInitializer& ObejectInitializer);
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UBehaviorTree* GetBehaviorTree();
	APatrolPath* GetPatrolPath();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ULyraAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	TObjectPtr<ULyraAbilitySet> AbilitySet = nullptr;

	virtual void SetStartingAnimationLayer();
};
