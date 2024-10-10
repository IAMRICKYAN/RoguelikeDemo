// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SMagicProjectile.h"

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ASMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
