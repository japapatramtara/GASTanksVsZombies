// Fill out your copyright notice in the Description page of Project Settings.


#include "TVZAbilitySystemComponent.h"

int UTVZAbilitySystemComponent::RemoveAllActiveEffectsWithTag(const FGameplayTag& Tag)
{
	int Result = 0;

	//ActiveGameplayEffects
	const FGameplayEffectQuery Query = 
		FGameplayEffectQuery::MakeQuery_MatchAnyEffectTags(FGameplayTagContainer(Tag));

	Result = RemoveActiveEffects(Query);
	
	return Result;
}

FActiveGameplayEffectHandle UTVZAbilitySystemComponent::ApplyGameplayEffectSpecToTarget(
	const FGameplayEffectSpec& GameplayEffect, 
	UAbilitySystemComponent* Target, 
	FPredictionKey PredictionKey)
{
	return Super::ApplyGameplayEffectSpecToTarget(GameplayEffect, Target, PredictionKey);
}

FActiveGameplayEffectHandle UTVZAbilitySystemComponent::ApplyGameplayEffectSpecToSelf(
	const FGameplayEffectSpec& GameplayEffect, 
	FPredictionKey PredictionKey)
{
	return Super::ApplyGameplayEffectSpecToSelf(GameplayEffect, PredictionKey);
}

bool UTVZAbilitySystemComponent::RemoveActiveGameplayEffect(
	FActiveGameplayEffectHandle Handle, 
	int32 StacksToRemove)
{
	return Super::RemoveActiveGameplayEffect(Handle, StacksToRemove);
}

void UTVZAbilitySystemComponent::RemoveActiveGameplayEffectBySourceEffect(
	TSubclassOf<UGameplayEffect> GameplayEffect,
	UAbilitySystemComponent* InstigatorAbilitySystemComponent, 
	int32 StacksToRemove)
{
	Super::RemoveActiveGameplayEffectBySourceEffect(GameplayEffect, InstigatorAbilitySystemComponent, StacksToRemove);
}

void UTVZAbilitySystemComponent::NotifyAbilityCommit(UGameplayAbility* Ability)
{
	Super::NotifyAbilityCommit(Ability);
}

void UTVZAbilitySystemComponent::NotifyAbilityActivated(
	const FGameplayAbilitySpecHandle Handle,
	UGameplayAbility* Ability)
{
	Super::NotifyAbilityActivated(Handle, Ability);
}

void UTVZAbilitySystemComponent::NotifyAbilityFailed(
	const FGameplayAbilitySpecHandle Handle, 
	UGameplayAbility* Ability,
	const FGameplayTagContainer& FailureReason)
{
	Super::NotifyAbilityFailed(Handle, Ability, FailureReason);
}

int32 UTVZAbilitySystemComponent::HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
	return Super::HandleGameplayEvent(EventTag, Payload);
}

void UTVZAbilitySystemComponent::DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL,
	float& YPos)
{
	Super::DisplayDebug(Canvas, DebugDisplay, YL, YPos);
}

void UTVZAbilitySystemComponent::PrintDebug()
{
	Super::PrintDebug();
}

void UTVZAbilitySystemComponent::TargetConfirm()
{
	Super::TargetConfirm();
}

void UTVZAbilitySystemComponent::TargetCancel()
{
	Super::TargetCancel();
}

void UTVZAbilitySystemComponent::ConfirmAbilityTargetData(FGameplayAbilitySpecHandle AbilityHandle,
	FPredictionKey AbilityOriginalPredictionKey, const FGameplayAbilityTargetDataHandle& TargetData,
	const FGameplayTag& ApplicationTag)
{
	Super::ConfirmAbilityTargetData(AbilityHandle, AbilityOriginalPredictionKey, TargetData, ApplicationTag);
}

void UTVZAbilitySystemComponent::CancelAbilityTargetData(FGameplayAbilitySpecHandle AbilityHandle,
	FPredictionKey AbilityOriginalPredictionKey)
{
	Super::CancelAbilityTargetData(AbilityHandle, AbilityOriginalPredictionKey);
}
