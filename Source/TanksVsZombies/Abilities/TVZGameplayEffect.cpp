// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/TVZGameplayEffect.h"

UTVZGameplayEffect::UTVZGameplayEffect()
{
}

void UTVZGameplayEffect::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	Super::GetOwnedGameplayTags(TagContainer);
}

void UTVZGameplayEffect::PostInitProperties()
{
	Super::PostInitProperties();
}

void UTVZGameplayEffect::PostLoad()
{
	Super::PostLoad();
}

void UTVZGameplayEffect::PreSave(const ITargetPlatform* TargetPlatform)
{
	Super::PreSave(TargetPlatform);
}
