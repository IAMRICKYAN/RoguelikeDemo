// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SItemLever.generated.h"

UCLASS()
class ROGUELIKEDEMO_API ASItemLever : public AActor,public ISGameplayInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void Interact_Implementation(APawn* InstigatorPawn);
	
	// Sets default values for this actor's properties
	ASItemLever();

	UFUNCTION()
	void LeverSwitch();

	UPROPERTY(EditDefaultsOnly)
	float TargetPitch;


protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	TObjectPtr<UStaticMeshComponent> LeverMesh;
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
