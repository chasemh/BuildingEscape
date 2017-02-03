// Copyright Chase Hennion 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;


private: 
	UPROPERTY( EditAnywhere )
	float OpenAngle = 45.0f;

	UPROPERTY( EditAnywhere )
	ATriggerVolume* PressurePlate;

	UPROPERTY( EditAnywhere )
	float DoorCloseDelay = 0.5f;

	float LastDoorOpenTime;

	FRotator InitialRotation;

	AActor* ActorThatOpens; // Remember Pawn inherits from Actor
	AActor* Owner; // The owning door
	
};
