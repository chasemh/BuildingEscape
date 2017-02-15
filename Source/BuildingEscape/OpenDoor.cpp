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
	if ( !PressurePlate ) {
		UE_LOG( LogTemp, Error, TEXT( "PressurePlate is not initialized! Is a trigger volume attached to %s?" ), *(Owner->GetName()) );
		return;
	}
	InitialRotation = Owner->GetActorRotation();
	InitialLocation = Owner->GetActorLocation();

	
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the Trigger Volume every frame 
	if ( GetTotalMassOfActorsOnPlate() > TriggerMass ) {
		// Open the door
		OnOpen.Broadcast();
	}
	else if ( TimedPlate ) {
		OnClose.Broadcast();
	}

}

float UOpenDoor::GetTotalMassOfActorsOnPlate() 
{
	float TotalMass = 0.0f;

	if ( !PressurePlate ) { return TotalMass; }

	// Find all of the overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors( OUT OverlappingActors );

	// Iterate through the actors adding their masses
	for ( const auto* Actor : OverlappingActors ) {
		//UE_LOG( LogTemp, Warning, TEXT( "Actor %s on pressure plate!" ), *(Actor->GetName()) );

		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

		//UE_LOG( LogTemp, Warning, TEXT( "Total Mass in kg on Plate: %.3f" ), TotalMass );
	}
	
	return TotalMass;
}
