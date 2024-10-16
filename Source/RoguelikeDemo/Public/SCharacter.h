// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SAttributeComponent.h"
#include "SInteractionComponent.h"
#include "Actions/SActionComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SCharacter.generated.h"




UCLASS()
class ROGUELIKEDEMO_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASCharacter();

protected:

	FTimerHandle PrimaryAttackTimerHandle;

	float Intime;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName;
	
	UPROPERTY(VisibleAnywhere,Category = "Components" )
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<UCameraComponent> CameraComp;
	

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	TObjectPtr<USActionComponent> ActionComp;

	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<USInteractionComponent> InteractionComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components")
	TObjectPtr<USAttributeComponent> AttributeComp;

	//Input System
	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput|Basic")
	TObjectPtr<UInputAction> Input_Move;

	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput|Basic")
	TObjectPtr<UInputAction> Input_LookMouse;
	
	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput|Basic")
	TObjectPtr<UInputAction> Input_Jump;

	//Attack
	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput|Attack")
	TObjectPtr<UInputAction> Input_Attack;

	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput|Attack")
	TObjectPtr<UInputAction> Input_BlackHoleAttack;

	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput|Attack")
	TObjectPtr<UInputAction> Input_Dash;



	//Interaction
	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput|Interaction")
	TObjectPtr<UInputAction> Input_Interact;

	virtual  void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;



public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Action_Move(const FInputActionValue& InputValue);

	void Action_LookMouse(const FInputActionValue& InputValue);

	void Action_PrimaryAttack();

	void Action_PrimaryInteract();

	void Action_BlackHoleAttack();

	void Action_Dash();
	

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);
	

};
