// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/SPowerup_Credits.h"

#include "SPlayerState.h"

ASPowerup_Credits::ASPowerup_Credits()
{
	CreditsAmount = 80;
}


void ASPowerup_Credits::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);
	
	if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
	{
		PS->AddCredits(CreditsAmount);
		HideAndCooldownPowerup();
	}
}

