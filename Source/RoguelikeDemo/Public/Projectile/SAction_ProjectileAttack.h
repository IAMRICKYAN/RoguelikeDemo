// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/SAction.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "SAction_ProjectileAttack.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKEDEMO_API USAction_ProjectileAttack : public USAction
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere, Category="Effects")
	FName HandSocketName;

	UPROPERTY(EditDefaultsOnly,Category="Attack")
	float AttackAnimDelay;

	UPROPERTY(EditAnywhere, Category="Attack")
	TObjectPtr<UAnimMontage> AttackAnim;

	UPROPERTY(EditAnywhere, Category="Effects")
	TObjectPtr<UParticleSystem> ImpactVFX;

	/* Sphere radius of the sweep to find desired target under crosshair. Adjusts final projectile direction */
	UPROPERTY(EditAnywhere, Category="Targeting")
	float SweepRadius;

	/* Fallback distance when sweep finds no collision under crosshair. Adjusts final projectile direction */
	UPROPERTY(EditAnywhere, Category="Targeting")
	float SweepDistanceFallback;

	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);

public:
	virtual void StartAction_Implementation(AActor* Instigator) override;

	USAction_ProjectileAttack();
};
