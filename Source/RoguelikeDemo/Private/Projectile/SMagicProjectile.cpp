// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SMagicProjectile.h"

#include "SAttributeComponent.h"

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		TObjectPtr<USAttributeComponent> AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));

		if(AttributeComp)
		{
			AttributeComp->ApplyHealthChanged(-20.0f);
			UE_LOG(LogTemp, Warning, TEXT("Magic Projectile Hit"));

			Destroy();
		}
	}
}

void ASMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
}
