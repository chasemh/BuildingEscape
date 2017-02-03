// Copyright Chase Hennion 2017

#include "BuildingEscape.h"
#include "Grabber.h"

// Defining a macro that doesn't change anything
// Currently being used as a marker for out parameters
#define OUT

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

	UE_LOG( LogTemp, Warning, TEXT( "Grabber reporting for duty!" ) );
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Get player view point this tick
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( OUT PlayerLocation, OUT PlayerRotation );
	
	// UE_LOG( LogTemp, Warning, TEXT( "Location: %s Rotation: %s" ), *PlayerLocation.ToString(), *PlayerRotation.ToString() );

	// Draw a red trace in the world to visualize

	// LineTraceEnd = PlayerLocation + LineTraceDirection * Reach

	//FVector LineTraceEnd = PlayerLocation + FVector( 0.f, 0.f, 50.f );
	FVector LineTraceEnd = PlayerLocation + ( PlayerRotation.Vector() * Reach );

	// Ray-cast out to reach distance
	DrawDebugLine(
		GetWorld(),
		PlayerLocation,
		LineTraceEnd,
		FColor( 255, 0, 0 ),
		false,
		0.f,
		0.f,
		10.f
	);

	/// Setup query parameters
	FCollisionQueryParams TraceParams( FName( TEXT( "" ) ), false, GetOwner() );

	/// Line-trace (AKA ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams( ECollisionChannel::ECC_PhysicsBody ),
		TraceParams
	);

	/// See what what objects we hit
	AActor* ActorHit = Hit.GetActor();
	if ( ActorHit )
	{
		UE_LOG( LogTemp, Warning, TEXT( "Hit: %s" ), *( ActorHit->GetName() ) )
	}

}

