// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SProjectileBase.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASProjectileBase::ASProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->InitSphereRadius(12.0f);
	RootComponent = SphereComp;

	ImpactVFX = CreateDefaultSubobject<UParticleSystem>(TEXT("EffectComp"));
	/*ImpactVFX->SetupAttachment(SphereComp);*/

	VFXComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFXComp"));
	VFXComp->SetupAttachment(RootComponent);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(RootComponent);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 4000.0f;
	MovementComp->MaxSpeed = 8000.0f;
	//这表明物体的旋转将会跟随其速度向量。也就是说，物体将会朝它移动的方向旋转，
	//这对于模拟例如子弹或者火箭这样的物体是很常见的，这些物体的尾部通常指向它们移动的反方向。
	MovementComp->bRotationFollowsVelocity = true;
	//这表示物体的初始速度是相对于物体自身的局部空间来定义的，而不是世界空间。
	//局部空间意味着速度向量是相对于物体自身的方向和坐标系统。如果这个属性设置为false，那么初始速度将会在世界空间中定义，与物体的朝向无关。
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->Bounciness = 0.3f;
	MovementComp->ProjectileGravityScale = 0.0f;

	ImpactShakeInnerRadius = 0.0f;
	ImpactShakeOuterRadius = 1500.0f;
	
}

void ASProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentHit.AddDynamic(this, &ASProjectileBase::OnActorHit);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ASProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if((OtherActor!=nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if( OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity()*120.0f, GetActorLocation());
		}
		Explode();
	}

}

void ASProjectileBase::Explode_Implementation()
{

	
	if(ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation(),true,EPSCPoolMethod::AutoRelease);
		UGameplayStatics::PlaySoundAtLocation(this,ImpactSound,GetActorLocation());
		UGameplayStatics::PlayWorldCameraShake(this, ImpactShake, GetActorLocation(), ImpactShakeInnerRadius, ImpactShakeOuterRadius);

		Destroy();
	}
}


// Called when the game starts or when spawned
void ASProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ASProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

