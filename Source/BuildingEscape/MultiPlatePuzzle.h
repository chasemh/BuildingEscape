/*
Unreal Actor Component that creates a sequenced pressure plate puzzle using
trigger volumes. This puzzle is solved when the player correctly intersects
each trigger volume in the correct order. When the player intersects a volume
out of order, the puzzle resets.

Copyright Chase Hennion 2017
*/

#pragma once

#include "Components/ActorComponent.h"
#include "MultiPlatePuzzle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FMultiPlatePuzzleEvent );

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UMultiPlatePuzzle : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMultiPlatePuzzle();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Gets the index of the plate that the plaer is overlapping or returns -1 if no plate is overlapped
	int32 GetOverlappingPlateIndex();

	// Blueprint event that is broadcast the entire puzzle has been correctly solved
	UPROPERTY( BlueprintAssignable )
	FMultiPlatePuzzleEvent OnSolved;

	// Blueprint event that is broadcast when the next plate in the sequence has been intersected by the player
	UPROPERTY( BlueprintAssignable )
	FMultiPlatePuzzleEvent OnCorrectPlate;

	// Blueprint event that is broadcast when the player intersects an incorrect plate that is out of sequence. Plates that have already been intersected in the correct order are ignored.
	UPROPERTY( BlueprintAssignable )
	FMultiPlatePuzzleEvent OnWrongPlate;

private:

	// The player actor
	AActor* Player = nullptr;

	// An array of pressure plates trigger volumes that must be intersected in order.
	UPROPERTY( EditAnywhere )
	TArray< ATriggerVolume* > PressurePlates;
	
	// The index of the next plate that must be intersected to continue the puzzle
	int32 NextPlateIndex = 0;
	
};
