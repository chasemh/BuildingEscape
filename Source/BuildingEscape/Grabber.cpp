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
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	SetupInputComponent();
	
}

/// Look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if ( PhysicsHandle ) {
		/// Physics Handle was found
		UE_LOG( LogTemp, Warning, TEXT( "UPhysicsHandleComponent found for %s" ), *(GetOwner()->GetName()) )
	}
	else {
		UE_LOG( LogTemp, Error, TEXT( "Could not find UPhysicsHandleComponent for %s" ), *(GetOwner()->GetName()) )
	}
}

/// Look for the attached Input Componenet, appears at runtime
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if ( InputComponent ) {
		/// Input Component was found
		UE_LOG( LogTemp, Warning, TEXT( "UInputComponent found for %s" ), *(GetOwner()->GetName()) )
			// Bind the input actions
			// Read as "When input component triggered by key press (Special Enum), use this instance and invoke the method at this memory address
			InputComponent->BindAction( "Grab", IE_Pressed, this, &UGrabber::Grab );
			InputComponent->BindAction( "Grab", IE_Released, this, &UGrabber::Release );
	}
	else {
		UE_LOG( LogTemp, Error, TEXT( "Could not find UInputComponent for %s" ), *(GetOwner()->GetName()) )
	}
}

void UGrabber::Grab() 
{
	UE_LOG( LogTemp, Warning, TEXT( "Grab Pressed" ) );

	/// LINE TRACE Try and reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	// If we hit something then attach a physics handle
	if ( ActorHit ) {
		// Attach phyics handle 
		PhysicsHandle->GrabComponent(
			ComponentToGrab, // The object to grab
			NAME_None, // Not dealing with skeletons so no bone name is needed
			ComponentToGrab->GetOwner()->GetActorLocation(), // Where to grab the component
			true // Allow rotation
		);
	}
		
}

void UGrabber::Release()
{
	UE_LOG( LogTemp, Warning, TEXT( "Grab Released" ) );
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::ShowReachVector()
{
	// Get player view point this tick
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( OUT PlayerLocation, OUT PlayerRotation );

	// Ascertain the vector for the player's reach
	FVector LineTraceEnd = PlayerLocation + (PlayerRotation.Vector() * Reach);

	// Draw a red vector to visualize the reach distance
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
}



// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if ( DrawReachVector ) {
		ShowReachVector();
	}

	// If the physics handle is attached
	if ( PhysicsHandle->GrabbedComponent ) {

		// Get player view point this tick
		FVector PlayerLocation;
		FRotator PlayerRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( OUT PlayerLocation, OUT PlayerRotation );

		// LineTraceEnd = PlayerLocation + LineTraceDirection * Reach
		FVector LineTraceEnd = PlayerLocation + (PlayerRotation.Vector() * Reach);

		// Move the object that we are holding
		PhysicsHandle->SetTargetLocation( LineTraceEnd );
	}
		

}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	// Get player view point this tick
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( OUT PlayerLocation, OUT PlayerRotation );

	// LineTraceEnd = PlayerLocation + LineTraceDirection * Reach
	FVector LineTraceEnd = PlayerLocation + (PlayerRotation.Vector() * Reach);

	// Ray-cast out to reach distance

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
		UE_LOG( LogTemp, Warning, TEXT( "Hit: %s" ), *(ActorHit->GetName()) )
	}
	return Hit;
}
