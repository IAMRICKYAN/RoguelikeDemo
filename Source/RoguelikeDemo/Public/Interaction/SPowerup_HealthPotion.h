// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/SPowerupActor.h"
#include "SPowerup_HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKEDEMO_API ASPowerup_HealthPotion : public ASPowerupActor
{
	GENERATED_BODY()


public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	ASPowerup_HealthPotion();
	
};
