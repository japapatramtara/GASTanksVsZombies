// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TVZAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class TANKSVSZOMBIES_API UTVZAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	/**
	 * @return Count of removed effects
	 */
	int RemoveAllActiveEffectsWithTag(const FGameplayTag&);
/// Overriden from UAbilitySystemComponent
	FActiveGameplayEffectHandle ApplyGameplayEffectSpecToTarget(
		const FGameplayEffectSpec& GameplayEffect, 
		UAbilitySystemComponent* Target, 
		FPredictionKey PredictionKey=FPredictionKey()) override;
	
	FActiveGameplayEffectHandle ApplyGameplayEffectSpecToSelf(
		const FGameplayEffectSpec& GameplayEffect, 
		FPredictionKey PredictionKey = FPredictionKey()) override;

	bool RemoveActiveGameplayEffect(
		FActiveGameplayEffectHandle Handle, 
		int32 StacksToRemove = -1) override;

	void RemoveActiveGameplayEffectBySourceEffect(
		TSubclassOf<UGameplayEffect> GameplayEffect, 
		UAbilitySystemComponent* InstigatorAbilitySystemComponent, 
		int32 StacksToRemove = -1) override;

	virtual void NotifyAbilityCommit(UGameplayAbility* Ability) override;
	virtual void NotifyAbilityActivated(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability) override;
	virtual void NotifyAbilityFailed(
		const FGameplayAbilitySpecHandle Handle, 
		UGameplayAbility* Ability, 
		const FGameplayTagContainer& FailureReason) override;

	int32 HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload) override;

	void DisplayDebug(class UCanvas* Canvas, const class FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;
	void PrintDebug() override;

	virtual void TargetConfirm() override;
	virtual void TargetCancel() override;

	virtual void ConfirmAbilityTargetData(
		FGameplayAbilitySpecHandle AbilityHandle, 
		FPredictionKey AbilityOriginalPredictionKey, 
		const FGameplayAbilityTargetDataHandle& TargetData, 
		const FGameplayTag& ApplicationTag) override;

	virtual void CancelAbilityTargetData(
		FGameplayAbilitySpecHandle AbilityHandle, 
		FPredictionKey AbilityOriginalPredictionKey) override;
};
