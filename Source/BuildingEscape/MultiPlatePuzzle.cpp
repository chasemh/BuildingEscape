// Copyright Chase Hennion 2017

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

	// If player is overlapping the correct volume in the puzzle
		// Increment NextPlate
		// Emit an event so a sound is played
	// Else if the player is overlapping another, incorrect volume
		// Only check for the next plates in the puzzle so if the player hits a plate that they have already used, it doesn't reset the puzzle.
		// Reset the Puzzle
		// Set NextPlate to 0 
		// Emit an event so a sound can be played
	// If the puzzle is solved  <-- NextPlate == PressurePlates.Num()   <-- Could probably have this in the first if statement so it isn't checked every tick
		// Emit an event to open the door

	if ( !Player || !PressurePlates[0] || NextPlateIndex >= PressurePlates.Num() ) { return; }

	int32 OverlappingPlateIndex = GetOverlappingPlateIndex();
	if ( OverlappingPlateIndex != -1 ) {
		if ( OverlappingPlateIndex == NextPlateIndex ) {
			// Stepped on the right plate
			NextPlateIndex++;
			if ( NextPlateIndex == PressurePlates.Num() ) {
				//Puzzle has been solved
				// Emit an event to open the door
				OnSolved.Broadcast();
			}
			else {
				OnCorrectPlate.Broadcast();
			}
		}
		else if ( OverlappingPlateIndex > NextPlateIndex ) {
			// Stepped on the wrong plate
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
			//UE_LOG( LogTemp, Warning, TEXT( "Player standing on pressure plate %s!" ), *(PressurePlates[Index]->GetName()) )
			return Index;
		}
	}

	return -1;
}

