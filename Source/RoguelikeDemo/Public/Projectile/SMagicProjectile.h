// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/SProjectileBase.h"
#include "SMagicProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKEDEMO_API ASMagicProjectile : public ASProjectileBase
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageAmount;
	
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void PostInitializeComponents() override;

public:
 	ASMagicProjectile();
};
