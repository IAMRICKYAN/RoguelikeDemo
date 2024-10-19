// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGameplayInterface.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("su.InteractionDebugDraw"), false, TEXT("Enable Debug Lines for Interact Component."), ECVF_Cheat);

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	TraceRadius = 30.0f;
	TraceDistance = 500.0f;

}

// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TObjectPtr<APawn> MyPawn = Cast<APawn>(GetOwner());
	if(MyPawn->IsLocallyControlled())
	{
		FindBestInteractable();
	}
}


void USInteractionComponent::Interact()
{

	ServerInteract(FocusedActor);
	
}

void USInteractionComponent::ServerInteract_Implementation(AActor* InFocus)
{

	if(InFocus == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "No Focus Actor to interact.");
		return;
	}
	
	APawn* MyPawn = CastChecked<APawn>(GetOwner());
	ISGameplayInterface::Execute_Interact(InFocus, MyPawn);
}


void USInteractionComponent::FindBestInteractable()
{

	const bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();
	
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	TObjectPtr<AActor> MyOwner = GetOwner();

	//这里的EyeLocation并不是摄像机的位置信息，而是角色的位置加上角色定义的高度的位置
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + EyeRotation.Vector() * TraceDistance;

	TArray<FHitResult> Hits;
	
	FCollisionShape Shape;
	Shape.SetSphere(TraceRadius);
	
	//颜色判断
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	FocusedActor = nullptr;
	
	for(FHitResult Hit : Hits)
	{
		if (bDebugDraw)
		{
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, TraceRadius, 32, LineColor, false, 0.0f);
		}
		
		AActor* HitActor = Hit.GetActor();
		if(HitActor)
		{
			if(HitActor->Implements<USGameplayInterface>())
			{
				/*APawn* MyPawn = Cast<APawn>(MyOwner);
				ISGameplayInterface::Execute_Interact(HitActor, MyPawn);*/
				FocusedActor = HitActor;
				break;
			}
		}
		
	}
	
	if(bDebugDraw)
	{
		DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 0.0f);
	}  
	
	
	
}

