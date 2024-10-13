// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/SItemLever.h"



// Sets default values
ASItemLever::ASItemLever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeverMesh"));
	LeverMesh->SetupAttachment(BaseMesh);

	SelectedActor = CreateDefaultSubobject<AActor>(TEXT("SelectedActor"));
	
	TargetPitch = 60.0f;
}



void ASItemLever::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);
	LeverSwitch();
	TargetPitch = -TargetPitch;
}

void ASItemLever::LeverSwitch()
{
	float CurrentTarget = TargetPitch;
	LeverMesh->SetRelativeRotation(FRotator(CurrentTarget, 0, 0));
}

// Called when the game starts or when spawned
void ASItemLever::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASItemLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

