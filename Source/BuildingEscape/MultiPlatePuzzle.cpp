/*
Implementation of MultiPlatePuzzle.
See MultiPlatePuzzle.h for class details

Copyright Chase Hennion 2017
*/

#include "BuildingEscape.h"
#include "MultiPlatePuzzle.h"


// Sets default values for this component's properties
UMultiPlatePuzzle::UMultiPlatePuzzle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMultiPlatePuzzle::BeginPlay()
{
	Super::BeginPlay();

	// Get the player actor
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();

	if ( !Player ) {
		UE_LOG( LogTemp, Error, TEXT( "Could not get the first player controller actor for %s MultiPlatePuzzle!" ), *(GetOwner()->GetName()) );
	}

	// See if the PressurePlates array was populated with at least one element.
	if ( !PressurePlates[ 0 ] ) {
		UE_LOG( LogTemp, Error, TEXT( "Pressure plates for %s MultiPlatePuzzle have not been set!" ), *(GetOwner()->GetName()) );
	}

	NextPlateIndex = 0;
	
}


// Called every frame
void UMultiPlatePuzzle::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if ( !Player || !PressurePlates[0] || NextPlateIndex >= PressurePlates.Num() ) { return; }

	int32 OverlappingPlateIndex = GetOverlappingPlateIndex();
	if ( OverlappingPlateIndex != -1 ) {
		if ( OverlappingPlateIndex == NextPlateIndex ) {
			/// Stepped on the right plate
			NextPlateIndex++;
			if ( NextPlateIndex == PressurePlates.Num() ) {
				// Puzzle has been solved
				// Emit an event to open the door
				OnSolved.Broadcast();
			}
			else {
				// The next correct plate has been intersected. Emit an event to play a sound.
				OnCorrectPlate.Broadcast();
			}
		}
		else if ( OverlappingPlateIndex > NextPlateIndex ) {
			/// Stepped on a wrong plate
			// Reset the Puzzle
			NextPlateIndex = 0;
			// Emit a event to play a sound
			OnWrongPlate.Broadcast();
		}
	}
}

int32 UMultiPlatePuzzle::GetOverlappingPlateIndex()
{
	for( int32 Index = 0; Index < PressurePlates.Num(); ++Index ) {
		if ( PressurePlates[ Index ]->IsOverlappingActor( Player ) ) {
			return Index;
		}
	}

	return -1;
}

