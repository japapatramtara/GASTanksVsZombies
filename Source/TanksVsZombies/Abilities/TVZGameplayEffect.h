// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "TVZGameplayEffect.generated.h"

/**
 * 
 */
UCLASS()
class TANKSVSZOMBIES_API UTVZGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()

public:
	UTVZGameplayEffect();
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	virtual void PostInitProperties() override;
	virtual void PostLoad() override;
	virtual void PreSave(const class ITargetPlatform* TargetPlatform) override;
};
