/*
Unreal Actor Component that allows a door to be opened when a trigger volume
is intersected by a player or object with a set mass. This class is modified 
from the class provided by Ben Tristem in the Udemy Unreal Course.

Copyright Chase Hennion 2017
*/

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FDoorEvent );

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Blueprint event that is broadcast when the door is to be opened
	UPROPERTY( BlueprintAssignable )
	FDoorEvent OnOpen;

	// Blueprint event that is broadcast when the door is to be closed
	UPROPERTY( BlueprintAssignable )
	FDoorEvent OnClose;

private: 

	// The trigger volume that will make the door open when it is intersected
	UPROPERTY( EditAnywhere )
	ATriggerVolume* PressurePlate = nullptr;

	// The needed mass of the object(s) intersecting PressurePlate in order to trigger the door opening
	UPROPERTY( EditAnywhere )
	float TriggerMass = 50.f;

	// If set to true, the door will begin to close after stepping out of the PressurePlate volume. If false, the door will remain open.
	UPROPERTY( EditAnywhere )
    bool TimedPlate = true;

	// The initial rotation of the door in space. Used in Blueprint.
	FRotator InitialRotation;

	// The initial location of the door in space. Used in Blueprint.
	FVector InitialLocation;

	// The owning door
	AActor* Owner = nullptr; 

	// Returns the total mass in kg that is currently itersecting PressurePlate
	float GetTotalMassOfActorsOnPlate();
	
};
