// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SAction_ProjectileAttack.h"

USAction_ProjectileAttack::USAction_ProjectileAttack()
{
	HandSocketName = "Muzzle_01";
	AttackAnimDelay = 0.2f;
}



void USAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{

	Super::StartAction_Implementation(Instigator);
	if(TObjectPtr<ACharacter> Character = Cast<ACharacter>(Instigator))
	{
		Character->PlayAnimMontage(AttackAnim);
		UGameplayStatics::SpawnEmitterAttached(ImpactVFX, Character->GetMesh(), HandSocketName,FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);
		
		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);

		//GetWorld() 被调用来获取当前 USAction_ProjectileAttack 实例所在的游戏世界（UWorld）的引用。
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);
		

	}
}

void USAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	

	if(ensureAlways(ProjectileClass))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		// Ignore Player
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InstigatorCharacter);


		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);

				
		APlayerCameraManager* CurrentCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
		FVector TraceDirection = CurrentCamera->GetActorForwardVector();
		FVector TraceStart = CurrentCamera->GetCameraLocation();
		FVector TraceEnd = TraceStart + (TraceDirection * 5000);
		FHitResult Hit;

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
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
		
	}
	StopAction(InstigatorCharacter);
	
}