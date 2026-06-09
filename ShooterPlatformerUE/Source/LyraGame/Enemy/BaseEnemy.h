// All rights reserved to GameBox Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Teams/LyraTeamAgentInterface.h"
#include "BaseEnemy.generated.h"

class ULyraAbilitySystemComponent;
class UAbilitySystemComponent;
class UAnimationSetUpComponent;
class APatrolPath;
class ULyraAbilitySet;
class ULyraCombatSet;
class ULyraHealthSet;
class ULyraHealthComponent;

UCLASS()
class LYRAGAME_API ABaseEnemy : public ACharacter, public IAbilitySystemInterface, public ILyraTeamAgentInterface
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityExecutionFinished);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	TObjectPtr<UAnimationSetUpComponent> AnimationSetUpComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	TObjectPtr<UBehaviorTree> BehaviorTree = nullptr;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	TObjectPtr<APatrolPath> PatrolPath = nullptr;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	int32 TeamID = 5;
	
	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	TObjectPtr<const ULyraCombatSet> CombatSet = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	TObjectPtr<const ULyraHealthSet> HealthSet = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	TObjectPtr<const ULyraHealthComponent> HealthComponent = nullptr;

public:

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	ULyraAbilitySystemComponent* GetLyraAbilitySystemComponent() const;

	FOnAbilityExecutionFinished OnAbilityExecutionFinished;
	
	ABaseEnemy(const FObjectInitializer& ObejectInitializer);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UBehaviorTree* GetBehaviorTree();
	APatrolPath* GetPatrolPath();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndplayReason) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ULyraAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	TObjectPtr<ULyraAbilitySet> AbilitySet = nullptr;

	UFUNCTION()
	void OnHealthChanged(ULyraHealthComponent* SourceHealthComponent, float OldValue, float NewValue, AActor* SourceInstigator);

	virtual void SetStartingAnimationLayer();
};
