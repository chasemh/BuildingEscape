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
	
}

void UOpenDoor::OpenDoor()
{
	// Find the owner
	AActor* Owner = GetOwner();

	// Create a Rotator
	// Pitch, Yaw, Role
	FRotator NewRotation = FRotator( 0.0f, 60.0f, 0.0f );

	// Set the door rotation
	Owner->SetActorRotation( NewRotation );


	//FRotator Rot = GetOwner()->GetActorRotation();
	//UE_LOG( LogTemp, Warning, TEXT( "%s has rotation %s" ), *Owner, *Rot.ToString() );
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
	}
	
		
	
}

