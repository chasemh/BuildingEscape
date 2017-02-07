// Copyright Chase Hennion 2017

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

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
	if ( GetTotalMassOfActorsOnPlate() > 50.f ) { // TODO Make into a paramter or constant
		// Open the door
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// Check to see if it is time to close the door
	if ( GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay ) {
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() 
{
	float TotalMass = 0.0f;

	// Find all of the overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors( OUT OverlappingActors );

	// Iterate through the actors adding their masses
	for ( const auto* Actor : OverlappingActors ) {
		UE_LOG( LogTemp, Warning, TEXT( "Actor %s on pressure plate!" ), *(Actor->GetName()) );

		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

		UE_LOG( LogTemp, Warning, TEXT( "Total Mass in kg on Plate: %.3f" ), TotalMass );
	}
	
	return TotalMass;
}
