// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguelikeDemo/Public/SCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	CameraComp=CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	ActionComp=CreateDefaultSubobject<USActionComponent>(TEXT("ActionComp"));
	

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>(TEXT("InteractionComp"));

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComp"));

	
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this,&ASCharacter::OnHealthChanged);
	Intime =0.2f;
}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
 

void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
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
		EnhancedInputComponent->BindAction(Input_LookMouse,ETriggerEvent::Triggered,this,&ASCharacter::Action_LookMouse);
		EnhancedInputComponent->BindAction(Input_Move,ETriggerEvent::Triggered,this,&ASCharacter::Action_Move);
		EnhancedInputComponent->BindAction(Input_Jump,ETriggerEvent::Triggered,this,&ACharacter::Jump);
		EnhancedInputComponent->BindAction(Input_Attack,ETriggerEvent::Triggered,this,&ASCharacter::Action_PrimaryAttack);
		EnhancedInputComponent->BindAction(Input_Interact,ETriggerEvent::Triggered,this,&ASCharacter::Action_PrimaryInteract);
		EnhancedInputComponent->BindAction(Input_BlackHoleAttack,ETriggerEvent::Triggered,this,&ASCharacter::Action_BlackHoleAttack);
		EnhancedInputComponent->BindAction(Input_Dash,ETriggerEvent::Triggered,this,&ASCharacter::Action_Dash);
	}
}

void ASCharacter::Action_Move(const FInputActionValue& InputValue)
{
	FRotator ControlRot = GetControlRotation();
	//只与偏航角Yaw有关，其余设置为0
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	//从输入得到二维向量
	const FVector2D AxisValue = InputValue.Get<FVector2D>();

	//前后移动
	AddMovementInput(ControlRot.Vector(),AxisValue.Y);

	//左右移动
	const FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector,AxisValue.X);
}

void ASCharacter::Action_LookMouse(const FInputActionValue& InputValue)
{
	const FVector2d Value = InputValue.Get<FVector2d>();
	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}

void ASCharacter::Action_PrimaryAttack()
{
	ActionComp->StartActionByName(this,"PrimaryAttack");
}

void ASCharacter::Action_BlackHoleAttack()
{
	ActionComp->StartActionByName(this,"BlackHole");
}

void ASCharacter::Action_Dash()
{
	ActionComp->StartActionByName(this,"Dash");
}


void ASCharacter::Action_PrimaryInteract()
{
	if(InteractionComp)
	{
		InteractionComp->Interact();
	}
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	if(Delta<0.0f && NewHealth <= 0.0f)
	{
		TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(GetController());
		if(PlayerController)
		{
			DisableInput(PlayerController);
		}
	}
}








