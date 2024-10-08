// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguelikeDemo/Public/SCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp=CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp=CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComp");
	SkeletalMeshComp->SetupAttachment(RootComponent);

}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASCharacter::Action_ControllerYaw(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.Get<float>());
} 

void ASCharacter::Action_ControllerPitch(const FInputActionValue& Value)
{
	AddControllerPitchInput(Value.Get<float>());
}

void ASCharacter::Action_ForwardMove(const FInputActionValue& Value)
{
	AddMovementInput(GetActorForwardVector(),Value.Get<float>());
}

void ASCharacter::Action_RightMove(const FInputActionValue& Value)
{
	AddMovementInput(GetActorRightVector(),Value.Get<float>());
}


void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*PlayerInputComponent->BindAxis("MoveForward",this,&ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASCharacter::MoveRight);

	//转向取决于偏航角Yaw
	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	//抬头低头取决于仰俯角Pitch
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);*/

	if(APlayerController* PlayerController = CastChecked<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			//将增强输入子系统与我们创建的映射文件绑定
			EnhancedInputLocalPlayerSubsystem->AddMappingContext(InputMappingContext,0);
			
		}
	}

	//映射文件添加好后，我们还要与我们的Action进行绑定
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ControlYaw,ETriggerEvent::Triggered,this,&ASCharacter::Action_ControllerYaw);
		EnhancedInputComponent->BindAction(ControlPitch,ETriggerEvent::Triggered,this,&ASCharacter::Action_ControllerPitch);
		EnhancedInputComponent->BindAction(ForwardMove,ETriggerEvent::Triggered,this,&ASCharacter::Action_ForwardMove);
		EnhancedInputComponent->BindAction(RightMove,ETriggerEvent::Triggered,this,&ASCharacter::Action_RightMove);
	}
	
	
	
	

}




