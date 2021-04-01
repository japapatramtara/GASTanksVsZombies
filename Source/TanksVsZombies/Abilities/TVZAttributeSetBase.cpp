// Fill out your copyright notice in the Description page of Project Settings.

#include "TVZAttributeSetBase.h"
#include "TanksVsZombies.h"
#include "PawnWithAbilities.h"
#include "GameplayEffectExtension.h"
#include "GameplayTagContainer.h"


UTVZAttributeSetBase::UTVZAttributeSetBase()
	: Health(1.f)
	, MaxHealth(1.f)
	, Healing (0.f)
	, HealingMultiplier(1.f)
	, YawSpeed(180.f)
	, MoveSpeed(25.f)
	, DefensePower(1.f)
	, DamageMultiplier(1.f)
	, Damage(0.f)
{

}

void UTVZAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Health
	DOREPLIFETIME(UTVZAttributeSetBase, Health);
	DOREPLIFETIME(UTVZAttributeSetBase, MaxHealth);
	DOREPLIFETIME(UTVZAttributeSetBase, Healing);
	DOREPLIFETIME(UTVZAttributeSetBase, HealingMultiplier);

	// Speed
	DOREPLIFETIME(UTVZAttributeSetBase, YawSpeed);
	DOREPLIFETIME(UTVZAttributeSetBase, MoveSpeed);

	// Damage
	DOREPLIFETIME(UTVZAttributeSetBase, DefensePower);
	DOREPLIFETIME(UTVZAttributeSetBase, DamageMultiplier);
	DOREPLIFETIME(UTVZAttributeSetBase, Damage);

}

void UTVZAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTVZAttributeSetBase, Health, OldValue);
}

void UTVZAttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTVZAttributeSetBase, MaxHealth, OldValue);
}

void UTVZAttributeSetBase::OnRep_Healing(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTVZAttributeSetBase, Healing, OldValue);
}

void UTVZAttributeSetBase::OnRep_HealingMultiplier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTVZAttributeSetBase, HealingMultiplier, OldValue);
}

void UTVZAttributeSetBase::OnRep_YawSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTVZAttributeSetBase, YawSpeed, OldValue);
}

void UTVZAttributeSetBase::OnRep_MoveSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTVZAttributeSetBase, MoveSpeed, OldValue);
}

void UTVZAttributeSetBase::OnRep_DefensePower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTVZAttributeSetBase, DefensePower, OldValue);
}

void UTVZAttributeSetBase::OnRep_DamageMultiplier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTVZAttributeSetBase, DamageMultiplier, OldValue);
}

void UTVZAttributeSetBase::OnRep_Damage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTVZAttributeSetBase, Damage, OldValue);
}

void UTVZAttributeSetBase::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
	const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void UTVZAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// This is called whenever attributes change, so for max health we want to scale the current totals to match
	Super::PreAttributeChange(Attribute, NewValue);

	NewValue = NewValue > 0 ? NewValue : 0;

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	//else if (Attribute == GetYawSpeedAttribute())
	//{
	//	NewValue = NewValue > 0 ? NewValue : 0;
	//}
	//else if(Attribute = GetDefensePowerAttribute())
	//{
	//	NewValue = NewValue > 0 ? NewValue : 0;
	//}
}

void UTVZAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	// Compute the delta between old and new, if it is available
	float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		// If this was additive, store the raw delta value to be passed along later
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	// Get the Target actor, which should be our owner
	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	APawnWithAbilities* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<APawnWithAbilities>(TargetActor);
	}

	if (Data.EvaluatedData.Attribute == GetDamageAttribute() && GetHealth() > 0)
	{
		// Get the Source actor
		AActor* SourceActor = nullptr;
		AController* SourceController = nullptr;
		APawnWithAbilities* SourceCharacter = nullptr;
		if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
		{
			SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
			SourceController = Source->AbilityActorInfo->PlayerController.Get();
			if (SourceController == nullptr && SourceActor != nullptr)
			{
				if (APawn* Pawn = Cast<APawn>(SourceActor))
				{
					SourceController = Pawn->GetController();
				}
			}

			// Use the controller to find the source pawn
			if (SourceController)
			{
				SourceCharacter = Cast<APawnWithAbilities>(SourceController->GetPawn());
			}
			else
			{
				SourceCharacter = Cast<APawnWithAbilities>(SourceActor);
			}

			// Set the causer actor based on context if it's set
			if (Context.GetEffectCauser())
			{
				SourceActor = Context.GetEffectCauser();
			}
		}

		// Try to extract a hit result
		FHitResult HitResult;
		if (Context.GetHitResult())
		{
			HitResult = *Context.GetHitResult();
		}

		float LocalDamageMultiplier = 1;

		// Fire deals double the damage
		if (Data.EffectSpec.CapturedSourceTags.GetAggregatedTags()->HasTag(FGameplayTag::RequestGameplayTag(TEXT("Damage.Type.Fire"))))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Fire Damage"));

			LocalDamageMultiplier = 2;
		}

		// Store a local copy of the amount of damage done and clear the damage attribute
		const float LocalDamageDone = (GetDamage() * LocalDamageMultiplier) / GetDefensePower();
		SetDamage(0.f);

		if (LocalDamageDone > 0)
		{
			// Apply the health change and then clamp it
			const float OldHealth = GetHealth();
			SetHealth(FMath::Clamp(OldHealth - LocalDamageDone, 0.0f, GetMaxHealth()));

			if (TargetCharacter)
			{
				// This is proper damage
				TargetCharacter->HandleDamage(LocalDamageDone, HitResult, SourceTags, SourceCharacter, SourceActor);

				// Call for all health changes
				TargetCharacter->HandleHealthChanged(-LocalDamageDone, SourceTags);
			}
		}
	}
	//else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	//{
	//	// Handle other health changes such as from healing or direct modifiers
	//	// First clamp it
	//	SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

	//	if (TargetCharacter)
	//	{
	//		// Call for all health changes
	//		TargetCharacter->HandleHealthChanged(DeltaValue, SourceTags);
	//	}
	//}
	else if (Data.EvaluatedData.Attribute == GetHealingAttribute())
	{

		// Store a local copy of the amount of healing done and clear the healing attribute
		const float LocalHealingDone = GetHealing() * GetHealingMultiplier();
		SetHealing(0.f);

		if (LocalHealingDone > 0)
		{
			// Apply the health change and then clamp it
			const float OldHealth = GetHealth();
			SetHealth(FMath::Clamp(OldHealth + LocalHealingDone, 0.0f, GetMaxHealth()));

			if (TargetCharacter)
			{
				// Call for all health changes
				TargetCharacter->HandleHealthChanged(LocalHealingDone, SourceTags);
			}
		}
	}
}

