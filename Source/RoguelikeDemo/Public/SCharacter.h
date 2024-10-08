// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "SCharacter.generated.h"




UCLASS()
class ROGUELIKEDEMO_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASCharacter();

protected:
	UPROPERTY(VisibleAnywhere,Category = "Components" )
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere,Category = "Components")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere,Category = "Compenents")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp;

	//Input System
	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput|Basic")
	TObjectPtr<UInputAction> ForwardMove;

	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput|Basic")
	TObjectPtr<UInputAction> RightMove;

	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput|Basic")
	TObjectPtr<UInputAction> ControlPitch;
	
	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput|Basic")
	TObjectPtr<UInputAction> ControlYaw;
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Action_ControllerYaw(const FInputActionValue& Value); 
	void Action_ControllerPitch(const FInputActionValue& Value);
	void Action_ForwardMove(const FInputActionValue& Value);
	void Action_RightMove(const FInputActionValue& Value);

};
