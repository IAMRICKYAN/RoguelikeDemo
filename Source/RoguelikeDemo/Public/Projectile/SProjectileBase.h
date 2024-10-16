// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"
#include "SProjectileBase.generated.h"

UCLASS()
class ROGUELIKEDEMO_API ASProjectileBase : public AActor
{
	GENERATED_BODY()
	

	

protected:

	UPROPERTY()
	float ImpactShakeInnerRadius;

	UPROPERTY()
	float ImpactShakeOuterRadius;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	TObjectPtr<USphereComponent> SphereComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	TObjectPtr<UProjectileMovementComponent> MovementComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	TObjectPtr<UAudioComponent> AudioComp;

	UPROPERTY(EditDefaultsOnly,Category="Effects")
	TObjectPtr<UParticleSystem> ImpactVFX;

	UPROPERTY(EditDefaultsOnly,Category="Effects")
	TObjectPtr<UParticleSystemComponent> VFXComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<USoundCue> ImpactSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<UCameraShakeBase> ImpactShake;

	


	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Explode();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:
	// Sets default values for this actor's properties
	ASProjectileBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
