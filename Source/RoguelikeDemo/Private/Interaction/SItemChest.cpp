// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/SItemChest.h"

#include "Net/UnrealNetwork.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASItemChest::ASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	Treasure = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Treasure"));
	Treasure->SetupAttachment(BaseMesh);
	

	VFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFX"));
	VFX->SetupAttachment(Treasure);
	VFX->bAutoActivate = false;

	bIsLidClosed = true;
	TargetPitch = 120.f;

	SetReplicates(true);
	
	


}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);
	bIsLidClosed = !bIsLidClosed;
	OnRep_LidOpend();
}

void ASItemChest::OnRep_LidOpend()
{
	float CurrentPitch = bIsLidClosed ? TargetPitch : 0.f;
	LidMesh->SetRelativeRotation(FRotator(CurrentPitch, 0, 0));
}


void ASItemChest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASItemChest, bIsLidClosed);
}

