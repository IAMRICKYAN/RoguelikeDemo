// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/SPowerup_HealthPotion.h"

#include "SAttributeComponent.h"
#include "SPlayerState.h"


ASPowerup_HealthPotion::ASPowerup_HealthPotion()
{
	CreditCost = 50;
}


void ASPowerup_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);

	
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	TObjectPtr<USAttributeComponent> AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
	// 检查使用者是否生命值已满
	if (ensure(AttributeComp) && !AttributeComp->IsFullHealth())
	{
		if(ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
		{
			// 只在成功治疗时进入冷却
			if (PS->RemoveCredits(CreditCost) && AttributeComp->ApplyHealthChanged(this, AttributeComp->GetHealthMax()))
			{
				HideAndCooldownPowerup();
			}
			
		}
	}
}

