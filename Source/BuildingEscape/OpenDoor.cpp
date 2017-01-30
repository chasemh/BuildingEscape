// Copyright Chase Hennion 2017

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Get the player controller
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
	InitialRotation = Owner->GetActorRotation();
	
}

void UOpenDoor::OpenDoor()
{
	// Open the door
	Owner->SetActorRotation( FRotator( 0.0f, OpenAngle, 0.0f ) );
}

void UOpenDoor::CloseDoor()
{
	// Close the door
	Owner->SetActorRotation( InitialRotation );
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the Trigger Volume every frame
	// If the ActorThatOpens is in the volume 
	if ( PressurePlate->IsOverlappingActor( ActorThatOpens ) ) {
		// Open the door
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// Check to see if it is time to close the door
	if ( GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay ) {
		CloseDoor();
	}
}

