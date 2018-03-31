// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay(); 
	UE_LOG(LogTemp, Warning, TEXT("OpenDoor meep") );	 
	TriggerActor = GetWorld()->GetFirstPlayerController()->GetPawn();	 

}

void UOpenDoor::OpenDoor() const
{
	UE_LOG(LogTemp, Warning, TEXT("OpenDoor Bitches") );
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(TriggerVolume->IsOverlappingActor(TriggerActor)){
		UE_LOG(LogTemp, Warning, TEXT("OPEN !!!!") );	 
		GetOwner()->SetActorRotation(FRotator(0.f, -DoorOpenAngle, 0.0f));
	}else{
		GetOwner()->SetActorRotation(FRotator(0.f, 0.0f, 0.0f));
	}
	// ...
}

