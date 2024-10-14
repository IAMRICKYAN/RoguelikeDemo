// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROGUELIKEDEMO_API USInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void Interact();
	
	// Sets default values for this component's properties
	USInteractionComponent();

protected:

	UPROPERTY()
	TObjectPtr<AActor> FocusedActor;

	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor* InFocus);

	void FindBestInteractable();


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
