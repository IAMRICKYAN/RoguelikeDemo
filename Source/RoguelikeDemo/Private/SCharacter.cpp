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

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComp->SetupAttachment(RootComponent);

	
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
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
	if(ActionComp->StartActionByName(this,"PrimaryAttack"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Action_PrimaryAttack"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Wrong"));

	}
	
	//PlayAnimMontage(AttackAnim);
	/*
	GetWorldTimerManager().SetTimer(PrimaryAttackTimerHandle,this,&ASCharacter::Action_PrimaryAttack_Elapsed,Intime);
*/
}

/*void ASCharacter::Action_PrimaryAttack_Elapsed()
{
	SpawnProjectile(ProjectileClass);
}

void ASCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if(ensure(ClassToSpawn))
	{
		// 生成角度和坐标
		// 获取人物模型中手的坐标，GetSocketLocation可以获取骨骼中的插件
		const FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		// 未校正前的生成方位
		// const FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
		FActorSpawnParameters SpawnParams;
		// 无论任何情况都生成（无视重叠，碰撞，覆盖...）
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		// 将角色自身作为触发者传入，以便子弹判断正确的交互对象
		SpawnParams.Instigator = this;

		// 碰撞参数，忽略自身
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		// 获取Camera组件
		APlayerCameraManager* CurrentCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
		// 方向是摄像机视角的正前方（屏幕正中央），这里不要把手部模型的坐标传入，方向会偏
		FVector TraceDirection = CurrentCamera->GetActorForwardVector();
		// 起始位置是摄像机的位置
		FVector TraceStart = CurrentCamera->GetCameraLocation();
		// 终点是一段距离，后面的5000不固定
		FVector TraceEnd = TraceStart + (TraceDirection * 5000);
	
		FHitResult Hit;
		// Line Trace检测与障碍物的撞击点
		if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_GameTraceChannel1, Params))
		{
			// 将撞击点作为方向向量的终点位置
			TraceEnd = Hit.ImpactPoint;
		}
		// 起始点是我们的子弹生成点（手），终点是目标点，获得Rotation
		FRotator ProjRotation = (TraceEnd - HandLocation).Rotation();
		// 最终获得校正后的生成方位
		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
	
		// 在世界中生成
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);
	}
}*/





