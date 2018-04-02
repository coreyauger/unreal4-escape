// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(!PysicsHandle){
		UE_LOG(LogTemp, Error, TEXT("Could not find PhysicsHandle") );	 
	}
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(!InputComponent){
		UE_LOG(LogTemp, Error, TEXT("Could not find input component") );	 
	}else{
		UE_LOG(LogTemp, Warning, TEXT("Grabber has input component") );
		InputComponent->BindAction("Grab",IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab",IE_Released, this, &UGrabber::Drop);
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	FVector GrabberVector = PlayerLocation + PlayerRotation.Vector() * 100.0f;
	DrawDebugLine(GetWorld(), PlayerLocation, GrabberVector, FColor::Red, false, 0.0f, 0.0f, 5.0f);
	if(PysicsHandle && PysicsHandle->GrabbedComponent){
		//UE_LOG(LogTemp, Warning, TEXT("move: %s"), *GrabberVector.ToString()  );	
		PysicsHandle->SetTargetLocation(GrabberVector);
	}
}

void UGrabber::Drop(){
	UE_LOG(LogTemp, Error, TEXT("Drop") );	 
	if(PysicsHandle)PysicsHandle->ReleaseComponent();
}

void UGrabber::Grab(){ 
	UE_LOG(LogTemp, Error, TEXT("Grab") );	 
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	FVector GrabberVector = PlayerLocation + PlayerRotation.Vector() * 100.0f;

	//UE_LOG(LogTemp, Warning, TEXT("UGrabber: %s"), *PlayerLocation.ToString() );
	
	UE_LOG(LogTemp, Warning, TEXT("move: %s"), *GrabberVector.ToString()  );	
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(Hit, PlayerLocation, GrabberVector, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);

	if(PysicsHandle && Hit.GetActor()){
		UE_LOG(LogTemp, Error, TEXT("Found") );	 
		//UE_LOG(LogTemp, Warning, TEXT("UGrabber Hit: %s"), *Hit.GetActor()->GetName() );
		PysicsHandle->GrabComponentAtLocation(Hit.GetComponent(), NAME_None, Hit.GetActor()->GetActorLocation());
	}
}

