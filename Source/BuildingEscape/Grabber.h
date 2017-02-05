// Copyright Chase Hennion 2017

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
	// How far ahead of the pawn we can reach
	float Reach = 100.f;

	// If set to true, draw the player's reach vector
	UPROPERTY( EditAnywhere )
	bool DrawReachVector = false;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Find and set the PhysicsHandle
	void FindPhysicsHandleComponent();

	// Find and setup the (assumed) attached InputComponent
	void SetupInputComponent();

	// Ray-cast and grab what is within reach
	void Grab();

	// Release grabbed object when grab is released
	void Release();

	// Visualize pawn's reach vector
	void ShowReachVector();

	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
	
};
