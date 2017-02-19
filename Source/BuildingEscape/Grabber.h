/*
Implementation of a "Grabber" Unreal Actor component. This component allows an
actor to grab, release and throw physics-enabled objects. This class is modified 
from the class provided by Ben Tristem in the Udemy Unreal Course.

Copyright Chase Hennion 2017
*/

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

// Stores the orientation and reach of a player
struct PlayerOrientation
{
	// The Cartesian location of the origin of the player. AKA The beginning of the reach vector.
	FVector Location;
	// The rotation of the player.
	FRotator Rotation;
	// A vector representation how far and in what direction the player can reach out and grab objects. AKA The end of the reach vector.
	FVector ReachVector;
};

UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
private:
	// How far ahead of the pawn the player can reach.
	float Reach = 100.f;

	// The component that is currently held.
	UPrimitiveComponent* HeldComponent = nullptr;

	// The 'strength' of the player's throw
	UPROPERTY( EditAnywhere )
	float ThrowImpulse = 8000.f;

	// If set to true, draw the player's reach vector
	UPROPERTY( EditAnywhere )
	bool DrawReachVector = false;

	// Player's attached Physics Handle
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	// Attached Input Component to allow for method invocation when certain keys are pressed
	UInputComponent* InputComponent = nullptr;

	// Find and set the PhysicsHandle
	void FindPhysicsHandleComponent();

	// Find and setup the (assumed) attached InputComponent
	void SetupInputComponent();

	// Ray-cast and grab what is within reach when grab key is prssed
	void Grab();

	// Release grabbed object when grab key is released
	void Release();

	// Throw a grabbed object
	void Throw();

	// Visualize player's reach vector in Unreal
	void DisplayReachVector();

	// Get the first physics body within the player's reach
	const FHitResult GetFirstPhysicsBodyInReach();

	// Gets the player's spatial orientation and reach vector
	const PlayerOrientation GetPlayerOrientation();
	
};
